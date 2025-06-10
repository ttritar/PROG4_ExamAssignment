#pragma once
#include "BaseComponent.h"

#include "BubbleState.h"

namespace cat
{
	class BubbleComponent : public dae::BaseComponent
	{
	public:
		// CTOR & DTOR
		//-------------
		BubbleComponent(std::shared_ptr<dae::GameObject> owner)
			: BaseComponent(*owner)
		{
			m_CurrentState = std::make_unique<ShootingState>();
			m_CurrentState->OnEnter(this);
		}
		virtual ~BubbleComponent() = default;
		BubbleComponent(const BubbleComponent& other) = delete;
		BubbleComponent(BubbleComponent&& other) = delete;
		BubbleComponent& operator=(const BubbleComponent& other) = delete;
		BubbleComponent& operator=(BubbleComponent&& other) = delete;

		// METHODS
		//-------------
		void Update(float deltaTime) override
		{
			// STATE
			//-----------------
			std::unique_ptr<BubbleState> newState = nullptr;
			if (m_CurrentState)
			{
				newState = m_CurrentState->Update(deltaTime);
			}
			if (newState)
			{
				ChangeState(std::move(newState));
			}
		}

		void ChangeState(std::unique_ptr<BubbleState> newState)
		{
			if (m_CurrentState) m_CurrentState->OnExit();
			m_CurrentState = std::move(newState);
			if (m_CurrentState) m_CurrentState->OnEnter(this);
		}


		glm::vec2 Direction{ 1,0 };

	private:
		std::unique_ptr<BubbleState> m_CurrentState;

	};
}
