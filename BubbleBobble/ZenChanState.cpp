#include "ZenChanState.h"

#include "ServiceLocator.h"
#include "ZenChanAIComponent.h"


#pragma region Chase
std::unique_ptr<cat::ZenChanState> cat::ChaseState::Update(float )
{
	const auto playerObj = m_pAIComponent->GetTarget();
	if (!playerObj) return nullptr;
	auto playerPos = playerObj->GetWorldPosition();
	auto enemyPos = m_pAIComponent->GetOwner()->GetWorldPosition();


	float directionX = playerPos.x - enemyPos.x;

	// H
	if (abs(directionX) > 5.f) 
	{
		m_pMovementComponent->Move(directionX > 0 ? 1.f : -1.f, 0.f);
	}
	else
	{
		m_pMovementComponent->Velocity.x = 0.f;
	}


	// STATE UPDATING
	//-----------------
	if (m_pAIComponent->GetTarget() == nullptr) return std::make_unique<PatrolState>();	
	return nullptr;

}

void cat::ChaseState::OnEnter(ZenChanAIComponent* ai)
{
	m_pAIComponent = ai;
	m_pMovementComponent = ai->GetOwner()->GetComponent<dae::MovementComponent>();
	if (!m_pMovementComponent)
	{
		throw std::runtime_error("ChaseState requires a MovementComponent");
	}

	// register players
	const auto& players = dae::ServiceLocator::GetInstance().GetPlayerSystem().GetPlayers();
	for (auto player : players)
	{
		m_pAIComponent->AddPlayer(player);
	}
}

void cat::ChaseState::OnExit()
{
}
#pragma endregion


#pragma region Patrol
std::unique_ptr<cat::ZenChanState> cat::PatrolState::Update(float deltaTime)
{
	auto enemyPos = m_pAIComponent->GetOwner()->GetWorldPosition();

	// change direction if hit a wall
	m_pMovementComponent->Move(m_Direction.x, m_Direction.y);
	if (!m_pMovementComponent->MoveLimits.canRight || !m_pMovementComponent->MoveLimits.canLeft)
	{
		m_Direction.x *= -1.f;
	}

	// choose if wanting to fall down or stay this level
	if (m_pMovementComponent->MoveLimits.canDown)
	{
		m_FallTimer += deltaTime;
		if (m_FallTimer >= m_FallBehCd)
		{
			m_FallTimer = 0.f;

			bool fall = rand() % 2 == 0;

			if (fall) {
				m_pMovementComponent->Move(0.f, 0.f);
				m_pMovementComponent->SetSpeed(0);
			}
			else {
				m_pMovementComponent->Jump();
				m_pMovementComponent->SetSpeed(m_PatrolSpeed);
			}
		}
	}
	else m_pMovementComponent->SetSpeed(m_PatrolSpeed);

	m_JumpTimer += deltaTime;
	if (m_JumpTimer >= m_JumpCd)
	{
		m_JumpTimer = 0.0f;

		// JUMP
		if (m_pMovementComponent->IsGrounded == true)
		{
			m_pMovementComponent->Jump();
		}
	}

	// STATE UPDATING
	//-----------------
	if (m_pAIComponent->GetTarget() != nullptr)	return std::make_unique<ChaseState>();
	return nullptr;
}

void cat::PatrolState::OnEnter(ZenChanAIComponent* ai)
{
	m_pAIComponent = ai;
	m_pMovementComponent = ai->GetOwner()->GetComponent<dae::MovementComponent>();
	if (!m_pMovementComponent)
	{
		throw std::runtime_error("PatrolState requires a MovementComponent");
	}

	m_pMovementComponent->SetSpeed(m_PatrolSpeed);

	// register players
	const auto& players = dae::ServiceLocator::GetInstance().GetPlayerSystem().GetPlayers();
	for (auto player : players)
	{
		m_pAIComponent->AddPlayer(player);
	}
}

void cat::PatrolState::OnExit()
{
	m_JumpTimer = 0.0f;
	m_JumpTimer = 5.f;
}
#pragma endregion
