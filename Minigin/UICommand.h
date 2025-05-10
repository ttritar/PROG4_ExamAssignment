#pragma once
#include "Command.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "ServiceLocator.h"

namespace cat
{
	class DamageCommand : public dae::GameActorCommand
	{
	protected:
		int m_damageAmount;
	public:
		DamageCommand(dae::GameObject* obj, int dmg)
			: GameActorCommand(obj),
			m_damageAmount( dmg)
		{
		}


		void Execute() override
		{
			if(m_buttonState.ReleasedThisFrame)
			{
				GetGameActor()->GetComponent<HealthComponent>()->TakeDamage(m_damageAmount);
			}
		}
	};


	class ScoreCommand : public dae::GameActorCommand
	{
	protected:
		int m_scoreAmount;
	public:
		ScoreCommand(dae::GameObject* obj, int amount)
			: GameActorCommand(obj),
			m_scoreAmount(amount),
			m_ServiceLocator(dae::ServiceLocator::GetInstance())
		{
		}


		void Execute() override
		{
			if (m_buttonState.ReleasedThisFrame)
			{
				GetGameActor()->GetComponent<ScoreComponent>()->GainScore(m_scoreAmount);

				const dae::sound_id soundId = static_cast<dae::sound_id>(dae::make_sdbm_hash("Attack"));

				m_ServiceLocator.GetSoundSystem().LoadSound(soundId, "../Data/Sounds/Attack.wav");
				m_ServiceLocator.GetSoundSystem().Play(soundId, 100);
			}
		}

	private:
		dae::ServiceLocator& m_ServiceLocator;

	};

}