#pragma once
#include "BaseComponent.h"
#include "ZenChanState.h"

// std
#include <memory>

namespace cat
{
	class ZenChanAIComponent : public dae::BaseComponent
	{
	public:
		// CTORS & DTORS
		//---------------
		ZenChanAIComponent(dae::GameObject& owner)
			:BaseComponent(owner)
		{
			m_CurrentState = std::make_unique<ChaseState>();
			m_CurrentState->OnEnter(this);
		}

		virtual ~ZenChanAIComponent() = default;
		ZenChanAIComponent(const ZenChanAIComponent& other) = delete;
		ZenChanAIComponent(ZenChanAIComponent&& other) = delete;
		ZenChanAIComponent& operator=(const ZenChanAIComponent& other) = delete;
		ZenChanAIComponent& operator=(ZenChanAIComponent&& other) = delete;


		// Methods
		//---------------
		void Update(float deltaTime);

		void ChangeState(std::unique_ptr<ZenChanState> newState);

		void AddPlayer(dae::GameObject* player)
		{
			if (player == nullptr) return;
			m_pPlayers.push_back(player);
		}

	private:
		std::unique_ptr<ZenChanState> m_CurrentState;
		dae::GameObject* m_pTarget = nullptr;
		std::vector<dae::GameObject*> m_pPlayers;
	};
}

