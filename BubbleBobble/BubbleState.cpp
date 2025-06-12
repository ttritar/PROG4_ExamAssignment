#include "BubbleState.h"

#include <random>

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

	
	auto toDir = m_TargetPosition - owner->GetWorldPosition();
	toDir = glm::normalize(toDir);
	m_pMovementComponent->Move(toDir.x, toDir.y);
	

	// STATE CHANGE
	//-----------------
	if (glm::distance(owner->GetWorldPosition(), m_TargetPosition) < 5.0f)
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

	// random target within area
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distX(300.f, 400.f);
	std::uniform_real_distribution<float> distY(100.f, 160.f);

	m_TargetPosition = glm::vec3(distX(gen), distY(gen), 0.f);
}

void cat::RisingState::OnExit()
{
	m_pMovementComponent->SetSpeed(0);
	m_pMovementComponent->Velocity = { 0,0 };
	m_pMovementComponent->MoveLimits = { true, true, true, true }; 
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