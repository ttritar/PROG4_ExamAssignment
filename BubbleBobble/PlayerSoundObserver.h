#pragma once
#include "Observer.h"
#include "ServiceLocator.h"

namespace cat
{
	class PlayerSoundObserver final : public dae::Observer
	{
	public:
		void Notify(const dae::Event& event, dae::GameObject* ) override
		{
			//----- JUMP -----
			if (event.id == dae::make_sdbm_hash("PlayerJumped"))
			{
				auto& ss = dae::ServiceLocator::GetInstance().GetSoundSystem();

				const dae::sound_id soundId = static_cast<dae::sound_id>(dae::make_sdbm_hash("PlayerJump"));
				ss.LoadSound(soundId, "../Data/Players/Jump.wav");
				ss.Play(soundId, 100);
			}
			//----- ATTACK -----
			else if (event.id == dae::make_sdbm_hash("PlayerAttacked"))
			{
				auto& ss = dae::ServiceLocator::GetInstance().GetSoundSystem();

				const dae::sound_id soundId = static_cast<dae::sound_id>(dae::make_sdbm_hash("PlayerAttack"));
				ss.LoadSound(soundId, "../Data/Players/Attack.wav");
				ss.Play(soundId, 100);
			}
		}

	};
}
