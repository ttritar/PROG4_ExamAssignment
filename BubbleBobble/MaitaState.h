#pragma once

#include <MovementComponent.h>

// std
#include <memory>

namespace cat
{
	class MaitaAIComponent;

	class MaitaState
	{
	public:
		virtual ~MaitaState() = default;
		virtual std::unique_ptr<MaitaState> Update(float deltaTime) = 0;
		virtual void OnEnter(MaitaAIComponent* ai) = 0;
		virtual void OnExit() = 0;
	};



	class WanderingState : public MaitaState
	{
	public:
		std::unique_ptr<MaitaState> Update(float deltaTime) override;
		void OnEnter(MaitaAIComponent* ai) override;
		void OnExit() override;

	private:
		MaitaAIComponent* m_pAIComponent = nullptr;
		MovementComponent* m_pMovementComponent = nullptr;

		float m_WanderTimer = 0.f;
		float m_Dx = 0.f;
		float m_Dy = 0.f;
		float m_WanderDuration = 2.f;
	};

	class ChasingState : public MaitaState
	{
	public:
		std::unique_ptr<MaitaState> Update(float deltaTime) override;
		void OnEnter(MaitaAIComponent* ai) override;
		void OnExit() override;

	private:
		MaitaAIComponent* m_pAIComponent = nullptr;
		MovementComponent* m_pMovementComponent = nullptr;
	};

	class TrappedState : public MaitaState
	{
	public:
		std::unique_ptr<MaitaState> Update(float deltaTime) override;
		void OnEnter(MaitaAIComponent* ai) override;
		void OnExit() override;
	private:
		MaitaAIComponent* m_pAIComponent = nullptr;
	};

	class DeadState : public MaitaState
	{
	public:
		std::unique_ptr<MaitaState> Update(float deltaTime) override;
		void OnEnter(MaitaAIComponent* ai) override;
		void OnExit() override;
	};

	
}

