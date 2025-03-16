#include "MovementComponent.h"
#include "TimeSingleton.h"

void dae::MovementComponent::Update(float)
{
}

// move
void dae::MovementComponent::SetSpeed(const float speed)
{
	m_speed = speed;
}

void dae::MovementComponent::Move(float dx, float dy)
{
	auto& time = Time::GetInstance();

	glm::vec3 pos = GetOwner()->GetLocalPosition();
	pos.x += dx * m_speed * time.DeltaTime;
	pos.y += dy * m_speed * time.DeltaTime;

	GetOwner()->SetLocalPosition(pos);
}

