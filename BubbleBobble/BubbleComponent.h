#pragma once
#include "BaseComponent.h"

#include "BubbleState.h"

namespace cat
{
	class BubbleComponent : public dae::BaseComponent
	{
	public:
		enum class TrappedEnemyType
		{
			None,
			ZenChan,
			Maita
		};

		// CTOR & DTOR
		//-------------
		BubbleComponent(dae::GameObject& owner)
			: BaseComponent(owner)
		{
			m_CurrentState = std::make_unique<ShootingState>();
			m_CurrentState->OnEnter(this);
		}
		BubbleComponent(dae::GameObject& owner, TrappedEnemyType enemy)
			: BaseComponent(owner)
		{
			m_CurrentState = std::make_unique<RisingState>();
			m_CurrentState->OnEnter(this);

			if (enemy == TrappedEnemyType::ZenChan)
			{
				owner.GetComponent<AnimationComponent>()->FrameData.row += 2;
			}
			else if (enemy == TrappedEnemyType::Maita)
			{
				owner.GetComponent<AnimationComponent>()->FrameData.row += 4;
			}
			HasTrapped = true;
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
			m_Lifetime += deltaTime;
			if (m_Lifetime > m_MaxLifetime)
			{
				GetOwner()->m_pendingRemoval = true;
			}

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
		bool HasTrapped{ false };
		bool Popped{false};

	private:
		std::unique_ptr<BubbleState> m_CurrentState;

		float m_Lifetime = 0.f;
		const float m_MaxLifetime = 20.f;
	};
}
