#include "BubbleState.h"

#include "BubbleComponent.h"


#pragma region ShootingState
std::unique_ptr<cat::BubbleState> cat::ShootingState::Update(float deltaTime)
{
	m_pMovementComponent->SetSpeed(m_ShootSpeed);
	m_pMovementComponent->Move(m_pBubbleComponent->Direction.x , m_pBubbleComponent->Direction.y);

	// STATE
	//-----------------
	m_ShootTimer += deltaTime;
	if (m_ShootTimer >= m_ShootDuration)
	{
		m_ShootTimer = 0.f;
		return std::make_unique<cat::RisingState>();
	}
	return nullptr; 
}

void cat::ShootingState::OnEnter(BubbleComponent* pBubble)
{
	m_pBubbleComponent = pBubble;

	m_pMovementComponent = m_pBubbleComponent->GetOwner()->GetComponent<MovementComponent>();
	if (!m_pMovementComponent)
	{
		throw std::runtime_error("ShootingState requires a MovementComponent on the Bubble's GameObject.");
	}
}

void cat::ShootingState::OnExit()
{
}
#pragma endregion


#pragma region RisingState
std::unique_ptr<cat::BubbleState> cat::RisingState::Update(float )
{
	m_pMovementComponent->SetSpeed(m_RiseSpeed);
	auto owner = m_pBubbleComponent->GetOwner();

	
	auto toDir = owner->GetWorldPosition() - m_TargetPosition;
	m_pMovementComponent->Move(toDir.x, toDir.y);
	

	// STATE CHANGE
	//-----------------
	if (owner->GetWorldPosition().y >= m_TargetPosition.y)
	{
		return std::make_unique<cat::StillState>();
	}
	return nullptr;
}

void cat::RisingState::OnEnter(BubbleComponent* pBubble)
{
	m_pBubbleComponent = pBubble;

	m_pMovementComponent = m_pBubbleComponent->GetOwner()->GetComponent<MovementComponent>();
	if (!m_pMovementComponent)
	{
		throw std::runtime_error("RisingState requires a MovementComponent on the Bubble's GameObject.");
	}
}

void cat::RisingState::OnExit()
{
}
#pragma endregion


#pragma region StillState
std::unique_ptr<cat::BubbleState> cat::StillState::Update(float )
{
	return nullptr;
}
void cat::StillState::OnEnter(BubbleComponent* )
{
}
void cat::StillState::OnExit()
{
}
#pragma endregion