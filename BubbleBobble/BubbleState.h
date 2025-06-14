#pragma once

#include <memory>
#include <vec3.hpp>

#include "AnimationComponent.h"
#include "MovementComponent.h"

namespace cat
{
	class BubbleComponent;


	class BubbleState
	{
	public:
		virtual ~BubbleState() = default;
		virtual std::unique_ptr<BubbleState> Update(float deltaTime) = 0;
		virtual void OnEnter(BubbleComponent* pBubble) = 0;
		virtual void OnExit() = 0;
	};


	class ShootingState : public BubbleState
	{
	public:
		std::unique_ptr<BubbleState> Update(float deltaTime) override;
		void OnEnter(BubbleComponent* pBubble) override;
		void OnExit() override;
	private:
		BubbleComponent* m_pBubbleComponent = nullptr;
		dae::MovementComponent* m_pMovementComponent = nullptr;

		float m_ShootTimer = 0.f;
		float m_ShootDuration = 0.5f;

		float m_ShootSpeed = 300.f;
	};

	class RisingState : public BubbleState
	{
	public:
		std::unique_ptr<BubbleState> Update(float deltaTime) override;
		void OnEnter(BubbleComponent* pBubble) override;
		void OnExit() override;
	private:
		BubbleComponent* m_pBubbleComponent = nullptr;
		dae::MovementComponent* m_pMovementComponent = nullptr;

		glm::vec3 m_TargetPosition{0};

		float m_RiseSpeed = 100.f; 
	};

	class StillState : public BubbleState
	{
	public:
		std::unique_ptr<BubbleState> Update(float deltaTime) override;
		void OnEnter(BubbleComponent* pBubble) override;
		void OnExit() override;
	};

	class PopState : public BubbleState
	{
	public:
		std::unique_ptr<BubbleState> Update(float deltaTime) override;
		void OnEnter(BubbleComponent* pBubble) override;
		void OnExit() override;
	private:
		BubbleComponent* m_pBubbleComponent = nullptr;
		AnimationComponent* m_pAnimationComponent = nullptr;

		float m_PopTimer = 0.f;
		float m_PopDuration = 0.5f; 
	};
}
