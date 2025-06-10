#include "ServiceLocator.h"

namespace dae
{
    std::unique_ptr<SoundSystem> ServiceLocator::_ss_instance = nullptr;
    
    void ServiceLocator::RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss)
    {
        _ss_instance = std::move(ss);
    }
}