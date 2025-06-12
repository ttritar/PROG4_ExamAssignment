#include "ZenChanState.h"

#include "ZenChanAIComponent.h"


#pragma region Chase
std::unique_ptr<cat::ZenChanState> cat::ChaseState::Update(float )
{
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
}

void cat::ChaseState::OnExit()
{
}
#pragma endregion