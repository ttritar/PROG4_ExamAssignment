#pragma once
#include "SoundSystem.h"

//std
#include <memory>



namespace dae
{
	class LoggingSoundSystem final : public SoundSystem
	{
	public:
		LoggingSoundSystem(std::unique_ptr<SoundSystem>& soundSystem)
		{
			m_SoundSystem = std::move(soundSystem);
		}


		void LoadSound(const sound_id id, const std::string& path) override;
		void Play(const sound_id id, const float volume) override;
		bool IsSoundPlaying(const sound_id id) override;

		void Stop(const sound_id id) override;
		void StopAllSounds() override;

	private:
		std::unique_ptr<SoundSystem> m_SoundSystem;
	};
}

