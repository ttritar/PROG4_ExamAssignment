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

	// simple ass jump buffer voor jouw isgrounded bullshit en da werkt 5 uur van mijn leven gone ong frfr
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// sleep time :) ily
	m_timeSinceJumpPress += deltaTime;
	if (m_IsGrounded && m_timeSinceJumpPress < MAX_JUMP_BUFFER) // NO JUMPIN IN AIR ???
	{
		m_timeSinceJumpPress = FLT_MAX;
		m_IsGrounded = false;

		m_Velocity.y -= m_JumpSpeed;
	}


	if ((m_Velocity.x < 0 && MoveLimits.left) || (m_Velocity.x > 0 && MoveLimits.right))
		pos.x += m_Velocity.x * deltaTime;
	if ((m_Velocity.y < 0 && MoveLimits.up) || (m_Velocity.y > 0 && MoveLimits.down))
		pos.y += m_Velocity.y * deltaTime;
	GetOwner()->SetLocalPosition(pos);

	MoveLimits = { true, true, true, true };
	m_Velocity.x = 0.f;
}

void cat::MovementComponent::Move(float dx, float dy)
{
	if ((dx < 0 && !MoveLimits.left) || (dx > 0 && !MoveLimits.right)) dx = 0;
	if ((dy < 0 && !MoveLimits.up) || (dy > 0 && !MoveLimits.down)) dy = 0;

	if (dx != 0)
		m_Velocity.x = dx * m_Speed;
	if (dy != 0)
		m_Velocity.y = dy * m_Speed;



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

	m_timeSinceJumpPress = 0.f; // reset jump press time
	
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
		m_Velocity.y -= m_GravitationalConstant; 
	}
}
