#pragma once
#include <memory>
#include <vector>

#include "BaseComponent.h"
#include "MovementComponent.h"
#include "EnemyState.h"

namespace cat
{
	class EnemyAIComponent : public dae::BaseComponent
	{
	public:
		// CTORS & DTORS
		//---------------
		EnemyAIComponent(std::shared_ptr<dae::GameObject> owner);
		virtual ~EnemyAIComponent() = default;
		EnemyAIComponent(const EnemyAIComponent& other) = delete;
		EnemyAIComponent(EnemyAIComponent&& other) = delete;
		EnemyAIComponent& operator=(const EnemyAIComponent& other) = delete;
		EnemyAIComponent& operator=(EnemyAIComponent&& other) = delete;

		// Methods
		//---------------
		void Update(float deltaTime) override;

		void ChangeState(std::unique_ptr<EnemyState> newState);

		virtual void Wander(float deltaTime)=0;
		virtual void Chase(float deltaTime)=0;


		// Getters & Setters
		void AddPlayer(std::shared_ptr<dae::GameObject> player)
		{
			if (player == nullptr) return;
			m_pPlayers.push_back(player);
		}

		void SetDetectionRadius(float radius) { m_DetectionRadius = radius; }

		std::shared_ptr<dae::GameObject> GetTarget() const { return m_pTarget; }
		bool GetIsPlayerSeen() const { return m_IsPlayerSeen; }
		bool GetIsTrapped() const { return m_IsTrapped; }
		bool GetIsDead() const { return m_IsDead; }

	protected:
		std::shared_ptr<dae::GameObject> m_pTarget = nullptr;


	private:
		// Private Methods
		//---------------
		void UpdatePlayerVisibility();

		// Private Members
		//---------------
		std::unique_ptr<EnemyState> m_CurrentState;

		bool m_IsPlayerSeen = false;
		std::vector<std::shared_ptr<dae::GameObject>> m_pPlayers;
		float m_DetectionRadius = 50.0f; 

		bool m_IsTrapped = false;
		bool m_IsDead = false;
	};
}
