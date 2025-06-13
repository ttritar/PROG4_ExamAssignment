#pragma once

#include "Singleton.h"

#include "SoundSystem.h"
#include "CollisionSystem.h"
#include "PlayerSystem.h"
#include "UIInputSystem.h"

// std
#include <memory>

namespace dae
{
	class UIInputSystem;

	class ServiceLocator final : public Singleton<ServiceLocator>
    {
    public:
        static SoundSystem& GetSoundSystem() { return *_ss_instance; }
        static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss);

		static CollisionSystem& GetCollisionSystem() { return *_cs_instance; }
		static void RegisterCollisionSystem(std::unique_ptr<dae::CollisionSystem>&& cs);

		static PlayerSystem& GetPlayerSystem() { return *_ps_instance; }
		static void RegisterPlayerSystem(std::unique_ptr<dae::PlayerSystem>&& ps);

		static UIInputSystem& GetUIInputSystem() { return *_ui_instance; }
		static void RegisterUIInputSystem(std::unique_ptr<UIInputSystem>&& ui);

    private:
        static std::unique_ptr<SoundSystem> _ss_instance;
		static std::unique_ptr<CollisionSystem> _cs_instance;
		static std::unique_ptr<PlayerSystem> _ps_instance;
		static std::unique_ptr<UIInputSystem> _ui_instance;
    };
}
