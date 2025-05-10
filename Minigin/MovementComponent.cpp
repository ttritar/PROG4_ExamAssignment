#include "MovementComponent.h"

#include "TimeSingleton.h"

// Methods
//---------------
void cat::MovementComponent::Update(float deltaTime)
{
	ApplyGravity();

	// Move based on the velocity (gets changed by commands and gravity and shit)
	glm::vec3 pos = GetOwner()->GetLocalPosition();
	pos.x += m_Velocity.x * deltaTime;
	pos.y += m_Velocity.y * deltaTime;
	GetOwner()->SetLocalPosition(pos);

}

void cat::MovementComponent::Move(float dx, float dy)
{
	auto& time = dae::Time::GetInstance();

	glm::vec3 pos = GetOwner()->GetLocalPosition();
	pos.x += dx * m_Speed * time.DeltaTime;
	pos.y += dy * m_Speed * time.DeltaTime;

	GetOwner()->SetLocalPosition(pos);
}

void cat::MovementComponent::Jump()
{
	if (m_JumpSpeed == 0) return; // jump "disabled

	if (!m_IsGrounded) return; // NO JUMPIN IN AIR ???
	m_IsGrounded = false;

	m_Velocity.y -= m_JumpSpeed;
}


// Private Methods
//---------------
void cat::MovementComponent::ApplyGravity()
{
	if (m_UsesGravity)
	{
		m_Velocity.y -= m_GravitationalConstant;
	}
}
