#include "MaitaState.h"

#include <memory>
#include <stdexcept>

#include "MaitaAIComponent.h"

// WanderingState
//------------------
std::unique_ptr<cat::MaitaState> cat::WanderingState::Update(float deltaTime)
{
	// Logic
	//-----------------
	m_WanderTimer += deltaTime;

	if (m_WanderTimer >= m_WanderDuration)
	{
		// goes to random direction
		m_Dx = (rand() % 2 == 0 ? 1 : -1) * 0.5f;
		m_Dy = (rand() % 2 == 0 ? 1 : -1) * 0.5f;

		// normalize 
		float magnitude = std::sqrt(m_Dx * m_Dx + m_Dy * m_Dy);

		if (magnitude > 0.0f)
		{
			m_Dx /= magnitude;
			m_Dy /= magnitude;
		}

		m_WanderTimer = 0.f;
	}

	m_pMovementComponent->Move(m_Dx, m_Dy);



	// Change State
	//-----------------
	if (m_pAIComponent->GetIsPlayerSeen())
	{
		return std::make_unique<ChasingState>();
	}
	else if (m_pAIComponent->IsTrapped)
	{
		return std::make_unique<TrappedState>();
	}

	return nullptr;
}

void cat::WanderingState::OnEnter(cat::MaitaAIComponent* ai)
{
	m_pAIComponent = ai;

	m_WanderTimer = 0.f;
	m_Dx = 0.f;
	m_Dy = 0.f;
	m_WanderDuration = 2.f + static_cast<float>(rand() % 3);

	m_pMovementComponent = ai->GetOwner()->GetComponent<MovementComponent>();
	if (!m_pMovementComponent)
	{
		throw std::runtime_error("WanderingState requires a MovementComponent");
	}
}

void cat::WanderingState::OnExit()
{
}


// ChasingState
//------------------
std::unique_ptr<cat::MaitaState> cat::ChasingState::Update(float)
{
	// Movement
	//-----------------
	auto playerPosition = m_pAIComponent->GetTarget()->GetWorldPosition();

	// calc direction to target
	float dx = playerPosition.x - m_pAIComponent->GetOwner()->GetWorldPosition().x;
	float dy = playerPosition.y - m_pAIComponent->GetOwner()->GetWorldPosition().y;

	// normalize
	float magnitude = std::sqrt(dx * dx + dy * dy);
	if (magnitude > 0.0f)
	{
		dx /= magnitude;
		dy /= magnitude;
	}

	m_pMovementComponent->Move(dx, dy);


	// AI Logic - Change State
	//-----------------
	if (m_pAIComponent->IsTrapped)
	{
		return std::make_unique<TrappedState>();
	}
	else if (!m_pAIComponent->GetIsPlayerSeen())
	{
		return std::make_unique<WanderingState>();
	}

	return nullptr;
}

void cat::ChasingState::OnEnter(cat::MaitaAIComponent* ai)
{
	m_pAIComponent = ai;

	m_pMovementComponent = ai->GetOwner()->GetComponent<MovementComponent>();
	if (!m_pMovementComponent)
	{
		throw std::runtime_error("ChasingState requires a MovementComponent");
	}
}

void cat::ChasingState::OnExit()
{
}


// TrappedState
//------------------
std::unique_ptr<cat::MaitaState> cat::TrappedState::Update(float )
{
	if (m_pAIComponent->IsDead)
	{
		return std::make_unique<DeadState>();
	}

	return nullptr; 

}

void cat::TrappedState::OnEnter(cat::MaitaAIComponent* ai)
{
	m_pAIComponent = ai;
}

void cat::TrappedState::OnExit()
{
}


// DeadState
//------------------
std::unique_ptr<cat::MaitaState> cat::DeadState::Update(float )
{
	return nullptr;
}

void cat::DeadState::OnEnter(cat::MaitaAIComponent*)
{
}

void cat::DeadState::OnExit()
{
}
