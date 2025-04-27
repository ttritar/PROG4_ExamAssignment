#include "LoggingSoundSystem.h"
#include <iostream>

namespace dae
{
    void LoggingSoundSystem::LoadSound(const sound_id id, const std::string& path)
    {
        std::cout << "Loading sound " << id << " from " << path << std::endl;
        m_SoundSystem->LoadSound(id, path);
    }

    void LoggingSoundSystem::Play(const sound_id id, const float volume)
    {
        std::cout << "Playing sound " << id << " with volume " << volume << std::endl;
        m_SoundSystem->Play(id, volume);
    }

    bool LoggingSoundSystem::IsSoundPlaying(const sound_id id)
    {
        std::cout << "Checking if sound " << id << " is playing" << std::endl;
        return  m_SoundSystem->IsSoundPlaying(id);
    }

    void LoggingSoundSystem::Stop(const sound_id id)
    {
        std::cout << "Stopping sound " << id << std::endl;
        m_SoundSystem->Stop(id);
    }

    void LoggingSoundSystem::StopAllSounds()
    {
        std::cout << "Stopping all sounds"  << std::endl;
        m_SoundSystem->StopAllSounds();
    }
}