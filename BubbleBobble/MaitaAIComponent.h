#pragma once

#include "MaitaState.h"

// std
#include <memory>


namespace cat
{
	class MaitaAIComponent : public dae::BaseComponent
	{
	public:
		// CTORS & DTORS
		//---------------
		MaitaAIComponent(dae::GameObject& owner)
			:BaseComponent(owner)
		{
			m_CurrentState = std::make_unique<WanderingState>();
			m_CurrentState->OnEnter(this);
		}

		virtual ~MaitaAIComponent() = default;
		MaitaAIComponent(const MaitaAIComponent& other) = delete;
		MaitaAIComponent(MaitaAIComponent&& other) = delete;
		MaitaAIComponent& operator=(const MaitaAIComponent& other) = delete;
		MaitaAIComponent& operator=(MaitaAIComponent&& other) = delete;


		// Methods
		//---------------
		void Update(float deltaTime);

		void ChangeState(std::unique_ptr<MaitaState> newState);


		// Getters & Setters
		void AddPlayer(dae::GameObject* player)
		{
			if (player == nullptr) return;
			m_pPlayers.push_back(player);
		}

		void SetDetectionRadius(float radius) { m_DetectionRadius = radius; }

		dae::GameObject* GetTarget() const { return m_pTarget; }
		bool GetIsPlayerSeen() const { return m_IsPlayerSeen; }


		bool IsDead = false;
		bool IsTrapped = false;

	private:
		// Private Methods
		//---------------
		void UpdatePlayerVisibility();

		// Private Members
		//---------------
		dae::MovementComponent* m_MovementComponent = nullptr;
		dae::GameObject* m_pTarget = nullptr;
		std::unique_ptr<MaitaState> m_CurrentState;

		bool m_IsPlayerSeen = false;
		std::vector<dae::GameObject*> m_pPlayers;
		float m_DetectionRadius = 50.0f;
	};
}
