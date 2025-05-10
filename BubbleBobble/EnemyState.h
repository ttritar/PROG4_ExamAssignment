#pragma once
#include <string>
#include <vec2.hpp>

namespace cat
{
	class EnemyAIComponent;

	class EnemyState
	{
	public:
		virtual ~EnemyState() = default;
		virtual void Update(EnemyAIComponent& ai, float deltaTime)=0;
		virtual void OnEnter(EnemyAIComponent& ai)=0;
		virtual void OnExit(EnemyAIComponent& ai)=0;
	};



	class WanderingState : public EnemyState
	{
	public:
		void Update(EnemyAIComponent& ai, float deltaTime) override;
		void OnEnter(EnemyAIComponent& ai) override;
		void OnExit(EnemyAIComponent& ai) override;
	};

	class ChasingState : public EnemyState
	{
	public:
		void Update(EnemyAIComponent& ai, float deltaTime) override;
		void OnEnter(EnemyAIComponent& ai) override;
		void OnExit(EnemyAIComponent& ai) override;
	};

	class TrappedState : public EnemyState
	{
	public:
		void Update(EnemyAIComponent& ai, float deltaTime) override;
		void OnEnter(EnemyAIComponent& ai) override;
		void OnExit(EnemyAIComponent& ai) override;
	};

	class DeadState : public EnemyState
	{
	public:
		void Update(EnemyAIComponent& ai, float deltaTime) override;
		void OnEnter(EnemyAIComponent& ai) override;
		void OnExit(EnemyAIComponent& ai) override;
	};
}

