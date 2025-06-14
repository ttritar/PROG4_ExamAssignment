#pragma once
#include "Observer.h"
#include "ServiceLocator.h"

namespace cat
{
	class PlayerSoundObserverComponent final : public dae::BaseComponent, public dae::Observer
	{
	public:
		void Notify(const dae::Event& event, dae::GameObject* ) override
		{
			//----- JUMP -----
			if (event.id == dae::make_sdbm_hash("PlayerJumped"))
			{
				auto& ss = dae::ServiceLocator::GetInstance().GetSoundSystem();

				const dae::sound_id soundId = static_cast<dae::sound_id>(dae::make_sdbm_hash("PlayerJump"));
				ss.LoadSound(soundId, "Players/Jump.wav");
				ss.Play(soundId, 100);
			}
			//----- ATTACK -----
			else if (event.id == dae::make_sdbm_hash("PlayerAttacked"))
			{
				auto& ss = dae::ServiceLocator::GetInstance().GetSoundSystem();

				const dae::sound_id soundId = static_cast<dae::sound_id>(dae::make_sdbm_hash("PlayerAttack"));
				ss.LoadSound(soundId, "Players/Attack.wav");
				ss.Play(soundId, 100);
			}
		}


		// CTOR & DTOR
		//--------------
		PlayerSoundObserverComponent(dae::GameObject& owner)
			: BaseComponent(owner)
		{
			// No initialization needed
		};
		virtual ~PlayerSoundObserverComponent() = default;
		PlayerSoundObserverComponent(const PlayerSoundObserverComponent& other) = delete;
		PlayerSoundObserverComponent(PlayerSoundObserverComponent&& other) = delete;
		PlayerSoundObserverComponent& operator=(const PlayerSoundObserverComponent& other) = delete;
		PlayerSoundObserverComponent& operator=(PlayerSoundObserverComponent&& other) = delete;
	};
}
