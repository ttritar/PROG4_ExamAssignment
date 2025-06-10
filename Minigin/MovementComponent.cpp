#include "MovementComponent.h"

#include <iostream>

#include "TimeSingleton.h"

// Methods
//---------------
void cat::MovementComponent::Update(float deltaTime)
{
	ApplyGravity();

	// Move based on the velocity (gets changed by commands and gravity and shit)
	glm::vec3 pos = GetOwner()->GetLocalPosition();

	if ((m_Velocity.x < 0 && MoveLimits.left) || (m_Velocity.x > 0 && MoveLimits.right))
		pos.x += m_Velocity.x * deltaTime;
	if ((m_Velocity.y < 0 && MoveLimits.up) || (m_Velocity.y > 0 && MoveLimits.down))
		pos.y += m_Velocity.y * deltaTime;
	GetOwner()->SetLocalPosition(pos);

	MoveLimits = { true, true, true, true };

}

void cat::MovementComponent::Move(float dx, float dy)
{
	auto& time = dae::Time::GetInstance();

	if ((dx < 0 && !MoveLimits.left) || (dx > 0 && !MoveLimits.right)) dx = 0;
	if ((dy < 0 && !MoveLimits.up) || (dy > 0 && !MoveLimits.down)) dy = 0;

	glm::vec3 pos = GetOwner()->GetLocalPosition();
	pos.x += dx * m_Speed * time.DeltaTime;
	pos.y += dy * m_Speed * time.DeltaTime;

	GetOwner()->SetLocalPosition(pos);


	// handle tex dir
	if (m_pTextureComponent)
	{
		if (dx > 0)
		{
			m_pTextureComponent->FlipFlag = SDL_FLIP_HORIZONTAL;
			m_Direction.x = 1;
		}
		else if ( dx < 0 )
		{
			m_pTextureComponent->FlipFlag = SDL_FLIP_NONE;
			m_Direction.x = -1;
		}
	}
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
		if (m_IsGrounded)
		{
			m_Velocity.y = 0; 
		}
		else
		{
			m_Velocity.y -= m_GravitationalConstant; 
		}
	}
}
