#pragma once

// std
#include <string>

namespace dae
{
	using sound_id = unsigned short;
	class SoundSystem
	{
	public:
		// CTOR & DTOR
		//-------------
		SoundSystem() = default;
		virtual ~SoundSystem() = default;

		SoundSystem(const SoundSystem& other) = delete;
		SoundSystem& operator=(const SoundSystem& other) = delete;
		SoundSystem(SoundSystem&& other) = delete;
		SoundSystem& operator=(SoundSystem&& other) = delete;


		// Methods
		//-------------
		virtual void LoadSound(const sound_id id, const std::string& path) = 0;
		virtual void Play(const sound_id id, const float volume) = 0;
		virtual bool IsSoundPlaying(sound_id id) = 0;
		virtual void Stop(sound_id id) = 0;
		virtual void StopAllSounds() = 0;
		virtual void ToggleMuteAllSounds() = 0;

	private:

	};
}

