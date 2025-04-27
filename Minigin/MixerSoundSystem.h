#pragma once
#include "SoundSystem.h"

//std
#include <memory>


namespace dae
{
	class MixerSoundSystem final : public SoundSystem
	{
    public:
        // CTOR & DTOR
        //-------------
        MixerSoundSystem();
        ~MixerSoundSystem() override;

        MixerSoundSystem(const MixerSoundSystem& other) = delete;
        MixerSoundSystem& operator=(const MixerSoundSystem& other) = delete;
        MixerSoundSystem(MixerSoundSystem&& other) = delete;
        MixerSoundSystem& operator=(MixerSoundSystem&& other) = delete;

        // Methods
        //-------------
        void LoadSound(const sound_id id, const std::string& path) override;
        void Play(const sound_id id, const float volume) override;
        bool IsSoundPlaying(const sound_id id) override;
        void Stop(const sound_id id) override;
        void StopAllSounds() override;

    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
	};
}

