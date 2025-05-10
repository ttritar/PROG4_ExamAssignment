#pragma once
#include "EnemyAIComponent.h"

namespace cat
{
	class MaitaAIComponent : public EnemyAIComponent
	{
	public:
		// CTORS & DTORS
		//---------------
		MaitaAIComponent(std::shared_ptr<dae::GameObject> owner)
			: EnemyAIComponent(owner)
		{
			m_MovementComponent = GetOwner()->GetComponent<MovementComponent>();
		}


		// Methods
		//---------------
		void Wander(float deltaTime) override;
		void Chase(float deltaTime) override;

	private:
		MovementComponent* m_MovementComponent;

		float m_WanderTimer = 0.f;
		float m_WanderDuration = 1.5f;
		float m_Dx = 0.f, m_Dy = 0.f;   
	};
}
