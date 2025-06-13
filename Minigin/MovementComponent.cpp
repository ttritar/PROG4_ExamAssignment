#include "MovementComponent.h"

#include <iostream>

#include "TimeSingleton.h"

// Methods
//---------------
void dae::MovementComponent::Update(float deltaTime)
{
	ApplyGravity();

	// Move based on the velocity (gets changed by commands and gravity and shit)
	glm::vec3 pos = GetOwner()->GetLocalPosition();


	// JUMPING
	if (m_JumpSpeed !=0)
	{
		m_timeSinceJumpPress += deltaTime;
		if (IsGrounded && m_timeSinceJumpPress < m_MAX_JUMP_BUFFER) // NO JUMPIN IN AIR ???
		{
			m_timeSinceJumpPress = FLT_MAX;
			IsGrounded = false;

			Velocity.y -= m_JumpSpeed;

			Event event{ dae::make_sdbm_hash("PlayerJumped") };
			GetOwner()->NotifyObservers(event);
		}
	}

	// ALL MOVEMENT
	if ((Velocity.x < 0 && MoveLimits.canLeft) || (Velocity.x > 0 && MoveLimits.canRight))
		pos.x += Velocity.x * deltaTime;
	if ((Velocity.y < 0 && MoveLimits.canUp) || (Velocity.y > 0 && MoveLimits.canDown))
		pos.y += Velocity.y * deltaTime;
	GetOwner()->SetLocalPosition(pos);

	// RESETS
	Velocity.x = 0.f;
}

void dae::MovementComponent::Move(float dx, float dy)
{
	if ((dx < 0 && !MoveLimits.canLeft) || (dx > 0 && !MoveLimits.canRight)) dx = 0;
	if ((dy < 0 && !MoveLimits.canUp) || (dy > 0 && !MoveLimits.canDown)) dy = 0;

	if (dx != 0)
		Velocity.x = dx * m_Speed;
	if (dy != 0)
		Velocity.y = dy * m_Speed;



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

void dae::MovementComponent::Jump()
{
	if (m_JumpSpeed == 0) return; 

	m_timeSinceJumpPress = 0.f; 
	
}


// Private Methods
//---------------
void dae::MovementComponent::ApplyGravity()
{
	if (m_UsesGravity)
	{
		if (IsGrounded)
		{
			Velocity.y = 0; 
		}
		else
		Velocity.y -= m_GravitationalConstant; 
	}
}
