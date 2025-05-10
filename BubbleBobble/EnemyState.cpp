#include "EnemyState.h"

#include <memory>
#include "EnemyAIComponent.h"
#include "MovementComponent.h"

// WanderingState
//------------------
void cat::WanderingState::Update(EnemyAIComponent& ai, float deltaTime)
{
	// Movement
	//-----------------
	ai.Wander(deltaTime);

	// AI Logic - Change State
	//-----------------
	if (ai.GetIsPlayerSeen())
	{
		ai.ChangeState(std::make_unique<ChasingState>());
	}
	else if (ai.GetIsTrapped())
	{
		ai.ChangeState(std::make_unique<TrappedState>());
	}

}

void cat::WanderingState::OnEnter(EnemyAIComponent& )
{
}

void cat::WanderingState::OnExit(EnemyAIComponent& )
{
}


// ChasingState
//------------------
void cat::ChasingState::Update(EnemyAIComponent& ai, float deltaTime)
{
	// Movement
	//-----------------
	ai.Chase(deltaTime);


	// AI Logic - Change State
	//-----------------
	if (ai.GetIsTrapped())
	{
		ai.ChangeState(std::make_unique<TrappedState>());
	}
	else if (!ai.GetIsPlayerSeen())
	{
		ai.ChangeState(std::make_unique<WanderingState>());
	}
}

void cat::ChasingState::OnEnter(EnemyAIComponent& )
{
}

void cat::ChasingState::OnExit(EnemyAIComponent& )
{
}


// TrappedState
//------------------
void cat::TrappedState::Update(EnemyAIComponent& ai, float )
{
	if (ai.GetIsDead())
	{
		ai.ChangeState(std::make_unique<DeadState>());
	}
}

void cat::TrappedState::OnEnter(EnemyAIComponent& )
{
}

void cat::TrappedState::OnExit(EnemyAIComponent& )
{
}


// DeadState
//------------------
void cat::DeadState::Update(EnemyAIComponent& , float )
{
}

void cat::DeadState::OnEnter(EnemyAIComponent& )
{
}

void cat::DeadState::OnExit(EnemyAIComponent& )
{
}
