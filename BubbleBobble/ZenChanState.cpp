#include "ZenChanState.h"

#include "ServiceLocator.h"
#include "ZenChanAIComponent.h"


#pragma region Chase
std::unique_ptr<cat::ZenChanState> cat::ChaseState::Update(float )
{
	if (!m_pAIComponent || !m_pMovementComponent) return nullptr;

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
	float dist = std::abs(directionX);
	if (dist > 300.f) // Arbitrary "lose interest" distance
	{
		// Return a new PatrolState or nullptr if none
		// return std::make_unique<PatrolState>();
		return nullptr; 
	}

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