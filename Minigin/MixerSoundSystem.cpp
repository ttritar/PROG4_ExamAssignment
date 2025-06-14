#include "MixerSoundSystem.h"
#include <SDL_mixer.h>

//std
#include <queue>
#include <mutex>
#include <SDL.h>
#include <unordered_map>

namespace dae
{
	class MixerSoundSystem::Impl
	{
	public:
		// CTOR & DTOR
		//--------------
		Impl()
			: m_IsThreadRunning(true), m_WorkerThread(&Impl::ProcessEvents, this)
		{
			Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC | MIX_INIT_MOD);
			Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
			Mix_AllocateChannels(32);
		}

		~Impl()
		{
			m_IsThreadRunning = false;
			m_Condition.notify_one();
			m_WorkerThread.join();

			for (auto& pair : m_SoundChunks) 
			{
				Mix_FreeChunk(pair.second);
			}

			Mix_CloseAudio();
			Mix_Quit();
			SDL_QuitSubSystem(SDL_INIT_AUDIO);
		}


		Impl(const Impl& other) = delete;
		Impl& operator=(const Impl& other) = delete;
		Impl(Impl&& other) = delete;
		Impl& operator=(Impl&& other) = delete;


		// Methods
		//--------------
		void LoadSound(const sound_id id, const std::string& path)
		{
			std::lock_guard<std::mutex> lock(m_QueueMutex);
			m_EventQueue.push({ SoundEventType::LOAD, id, 0, path });
			m_Condition.notify_one();
		}

		void Play(const sound_id id, const float volume )
		{
			std::lock_guard<std::mutex> lock(m_QueueMutex);
			m_EventQueue.push({ SoundEventType::PLAY, id, volume, "" });
			m_Condition.notify_one();
		}

		bool IsSoundPlaying(const sound_id id)
		{
			std::lock_guard<std::mutex> lock(m_PlayingChannelsMutex);

			return m_PlayingChannels.find(id) != m_PlayingChannels.end();
		}

		void Stop(const sound_id id)
		{
			std::lock_guard<std::mutex> lock(m_QueueMutex);
			m_EventQueue.push({ SoundEventType::STOP, id, 0, "" });
			m_Condition.notify_one();
		}

		void StopAllSounds()
		{
			std::lock_guard<std::mutex> lock(m_QueueMutex);
			m_EventQueue.push({ SoundEventType::STOP_ALL, 0, 0, "" });
			m_Condition.notify_one();
		}

		void ToggleMuteAllSounds()
		{
			std::lock_guard<std::mutex> lock(m_QueueMutex);
			m_EventQueue.push({ SoundEventType::MUTE_ALL, 0, 0, "" });
			m_Condition.notify_one();
		}

	private:
		enum class SoundEventType { 
			PLAY, 
			STOP, 
			STOP_ALL, 
			LOAD,
			MUTE_ALL
		};

		struct SoundEvent {
			SoundEventType type;
			sound_id id;
			float volume;
			std::string filePath;
		};

		// Private Methods
		//--------------------

		void ProcessEvents()
		{
			while (m_IsThreadRunning)
			{
				std::unique_lock<std::mutex> lock(m_QueueMutex);

				m_Condition.wait(
					lock, 
					[this]	()	{ return !m_EventQueue.empty() || !m_IsThreadRunning;	}
				);


				if (!m_IsThreadRunning) break;	//stop the moment the thread stops runnin


				SoundEvent event = m_EventQueue.front();
				m_EventQueue.pop();
				lock.unlock();

				switch (event.type)
				{
				case SoundEventType::PLAY:
					HandlePlayEvent(event);
					break;
				case SoundEventType::STOP:
					HandleStopEvent(event);
					break;
				case SoundEventType::STOP_ALL:
					HandleStopAllEvent();
					break;
				case SoundEventType::LOAD:
					HandleLoadEvent(event);
					break;
				case SoundEventType::MUTE_ALL:
					HandleMuteAllEvent();
				}
			}
		}

		void HandlePlayEvent(const SoundEvent& event)
		{
			auto it = m_SoundChunks.find(event.id);
			if (it != m_SoundChunks.end())
			{
				int channel = Mix_PlayChannel(-1, it->second, 0);
				if (channel != -1)
				{
					Mix_Volume(channel, static_cast<int>(event.volume));

					std::lock_guard<std::mutex> lock(m_PlayingChannelsMutex);
					m_PlayingChannels[event.id] = channel;
				}
			}
		}

		void HandleStopEvent(const SoundEvent& event)
		{
			std::lock_guard<std::mutex> lock(m_PlayingChannelsMutex);
			auto it = m_PlayingChannels.find(event.id);
			if (it != m_PlayingChannels.end())
			{
				Mix_HaltChannel(it->second);
				m_PlayingChannels.erase(it);
			}
		}

		void HandleStopAllEvent()
		{
			std::lock_guard<std::mutex> lock(m_PlayingChannelsMutex);
			Mix_HaltChannel(-1);
			m_PlayingChannels.clear();
		}

		void HandleLoadEvent(const SoundEvent& event)
		{
			auto it = m_SoundChunks.find(event.id);
			if (it != m_SoundChunks.end())
			{
				return;
			}

			Mix_Chunk* chunk = Mix_LoadWAV(event.filePath.c_str());
			if (chunk)
			{
				m_SoundChunks[event.id] = chunk;
			}
		}

		void HandleMuteAllEvent()
		{
			std::lock_guard<std::mutex> lock(m_PlayingChannelsMutex);
			if (m_IsMuted)
			{
				for (const auto& pair : m_PlayingChannels)
				{
					Mix_Volume(pair.second, MIX_MAX_VOLUME);
				}
			}
			else
			{
				for (const auto& pair : m_PlayingChannels)
				{
					Mix_Volume(pair.second, 0);
				}
			}
			m_IsMuted = !m_IsMuted;
		}

		// Private Datamembers
		//--------------------
		std::queue<SoundEvent> m_EventQueue;
		std::mutex m_QueueMutex;
		std::condition_variable m_Condition;
		std::unordered_map<sound_id, Mix_Chunk*> m_SoundChunks;
		std::unordered_map<sound_id, int> m_PlayingChannels;
		std::mutex m_PlayingChannelsMutex;
		std::atomic<bool> m_IsThreadRunning;
		std::thread m_WorkerThread;

		bool m_IsMuted{ false };
	};


	

	// MIXER SOUND SYSTEM METHODS
	//==============================

	MixerSoundSystem::MixerSoundSystem()
		:m_pImpl(std::make_unique<Impl>())
	{
	}

	MixerSoundSystem::~MixerSoundSystem() = default;

	void MixerSoundSystem::LoadSound(const sound_id id, const std::string& path)
	{
		m_pImpl->LoadSound(id, path);
	}

	void MixerSoundSystem::Play(const sound_id id, const float volume)
	{
		m_pImpl->Play(id, volume);
	}

	bool MixerSoundSystem::IsSoundPlaying(const sound_id id)
	{
		return m_pImpl->IsSoundPlaying(id);
	}

	void MixerSoundSystem::Stop(const sound_id id)
	{
		m_pImpl->Stop(id);
	}

	void MixerSoundSystem::StopAllSounds()
	{
		m_pImpl->StopAllSounds();
	}

	void MixerSoundSystem::ToggleMuteAllSounds()
	{
		m_pImpl->ToggleMuteAllSounds();
	}

}
