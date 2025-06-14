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
		BubbleComponent(dae::GameObject& owner);
		BubbleComponent(dae::GameObject& owner, TrappedEnemyType enemy);

		virtual ~BubbleComponent() = default;
		BubbleComponent(const BubbleComponent& other) = delete;
		BubbleComponent(BubbleComponent&& other) = delete;
		BubbleComponent& operator=(const BubbleComponent& other) = delete;
		BubbleComponent& operator=(BubbleComponent&& other) = delete;

		// METHODS
		//-------------
		void Update(float deltaTime) override;

		void ChangeState(std::unique_ptr<BubbleState> newState);


		glm::vec2 Direction{ 1,0 };
		bool HasTrapped{ false };
		TrappedEnemyType TrappedEnemy{ TrappedEnemyType::None };
		bool Popped{false};

	private:
		std::unique_ptr<BubbleState> m_CurrentState;

		float m_Lifetime = 0.f;
		const float m_MaxLifetime = 15.f;
	};
}
