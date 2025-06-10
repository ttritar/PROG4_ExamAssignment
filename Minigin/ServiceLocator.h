#pragma once

#include "Singleton.h"
#include "SoundSystem.h"
#include <memory>

namespace dae
{
    class ServiceLocator final : public Singleton<ServiceLocator>
    {
    public:
        static SoundSystem& GetSoundSystem() { return *_ss_instance; }
        static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss);

    private:
        static std::unique_ptr<SoundSystem> _ss_instance;
    };
}