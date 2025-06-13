#include "ServiceLocator.h"

namespace dae
{
	// SOUND SYSTEM
	//---------------------------
    std::unique_ptr<SoundSystem> ServiceLocator::_ss_instance = nullptr;
    
    void ServiceLocator::RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss)
    {
        _ss_instance = std::move(ss);
    }


	// COLLISION SYSTEM
	//---------------------------
    std::unique_ptr<CollisionSystem> ServiceLocator::_cs_instance = nullptr;

    void ServiceLocator::RegisterCollisionSystem(std::unique_ptr<dae::CollisionSystem>&& cs)
    {
		_cs_instance = std::move(cs);
    }


	// PLAYER SYSTEM
	//---------------------------
	std::unique_ptr<PlayerSystem> ServiceLocator::_ps_instance = nullptr;

    void ServiceLocator::RegisterPlayerSystem(std::unique_ptr<dae::PlayerSystem>&& ps)
    {
		_ps_instance = std::move(ps);
    }


	// UI INPUT SYSTEM
	//---------------------------
	std::unique_ptr<UIInputSystem> ServiceLocator::_ui_instance = nullptr;

    void ServiceLocator::RegisterUIInputSystem(std::unique_ptr<UIInputSystem>&& ui)
    {
		_ui_instance = std::move(ui);
    }
}
