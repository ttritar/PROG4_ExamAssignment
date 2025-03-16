#pragma once
#include "Command.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"

namespace dae
{
	class DamageCommand : public GameActorCommand
	{
	protected:
		int m_damageAmount;
	public:
		DamageCommand(GameObject* obj, int dmg)
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


	class ScoreCommand : public GameActorCommand
	{
	protected:
		int m_scoreAmount;
	public:
		ScoreCommand(GameObject* obj, int amount)
			: GameActorCommand(obj),
			m_scoreAmount(amount)
		{
		}


		void Execute() override
		{
			if (m_buttonState.ReleasedThisFrame)
			{
				GetGameActor()->GetComponent<ScoreComponent>()->GainScore(m_scoreAmount);
			}
		}
	};

}