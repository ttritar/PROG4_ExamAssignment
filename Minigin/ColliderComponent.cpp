#include "ColliderComponent.h"

#include <iostream>
#include <SDL_rect.h>
#include <SDL_render.h>

#include "MovementComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ServiceLocator.h"


dae::ColliderComponent::ColliderComponent(dae::GameObject& owner, ColliderInfo colliderInfo)
	:BaseComponent(owner),
	Info(colliderInfo)
{
	ServiceLocator::GetInstance().GetCollisionSystem().AddCollider(this);

	if (!Info.isStatic)
	{
		m_pMovementComponent = GetOwner()->GetComponent<dae::MovementComponent>();
	}
}

dae::ColliderComponent::~ColliderComponent()
{
	ServiceLocator::GetInstance().GetCollisionSystem().RemoveCollider(this);
}



void dae::ColliderComponent::FixedUpdate(float)
{
	if (Info.isStatic) return;
	m_pMovementComponent->MoveLimits = { true, true, true, true };

	auto physColliders = ServiceLocator::GetInstance().GetCollisionSystem().GetPhysicsColliders();
	auto triggerColliders = ServiceLocator::GetInstance().GetCollisionSystem().GetTriggerColliders();

	for (auto& coll : triggerColliders)
	{
		if (coll->GetOwner() == GetOwner()) continue;
		if (!CanCollideWith(coll)) continue;
		if (CheckCollision(coll))
		{
			HandleTriggerCollision(coll);
		}
	}

	if (m_pMovementComponent) m_pMovementComponent->IsGrounded=false;
	for (auto& coll : physColliders)
	{
		if (coll->GetOwner() == GetOwner()) continue;
		if (!CanCollideWith(coll)) continue;

		if (CheckCollision(coll))
		{
			HandlePhysicalCollision(coll);
		}
	}
}

void dae::ColliderComponent::DebugRendering() const
{
	auto sdlRenderer = dae::Renderer::GetInstance().GetSDLRenderer();

	if (Info.type == ColliderType::TopOnly) SDL_SetRenderDrawColor(sdlRenderer, 255, 100, 0, 1);
	if (Info.type == ColliderType::Solid) SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, 1);
	if (Info.type == ColliderType::Trigger) SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 0, 1);

	const SDL_Rect rect = SDL_Rect{
		static_cast<int> (GetOwner()->GetLocalPosition().x + Info.offset.x),
		static_cast<int> (GetOwner()->GetLocalPosition().y + Info.offset.y),
		static_cast<int> (Info.size.x),
		static_cast<int> (Info.size.y)
	};
	SDL_RenderDrawRect(sdlRenderer, &rect);

}

bool dae::ColliderComponent::CanCollideWith(const ColliderComponent* other) const
{
	if (Info.isStatic && other->Info.isStatic) return false;

	return (other->Info.tag & Info.collisionFilter) != 0;
}

bool dae::ColliderComponent::CheckCollision(const ColliderComponent* other) const
{
	glm::vec2 pos = glm::vec2{ GetOwner()->GetLocalPosition().x,GetOwner()->GetLocalPosition().y } + Info.offset;
	glm::vec2 otherPos = glm::vec2{ other->GetOwner()->GetLocalPosition().x,other->GetOwner()->GetLocalPosition().y } + other->Info.offset;

	return (
		pos.x < otherPos.x + other->Info.size.x &&
		pos.x + Info.size.x > otherPos.x &&
		pos.y < otherPos.y + other->Info.size.y &&
		pos.y + Info.size.y > otherPos.y
		);
}


void dae::ColliderComponent::HandlePhysicalCollision(const ColliderComponent* other)
{
	if (Info.isStatic || !m_pMovementComponent) return;

	const glm::vec3 pos = GetPosition();
	const glm::vec2 size = Info.size;
	const glm::vec3 otherPos = other->GetPosition();
	const glm::vec2 otherSize = other->Info.size;

	float dx = (pos.x + size.x / 2.0f) - (otherPos.x + otherSize.x / 2.0f);
	float dy = (pos.y + size.y / 2.0f) - (otherPos.y + otherSize.y / 2.0f);
	float overlapX = (size.x + otherSize.x) / 2.0f - std::abs(dx);
	float overlapY = (size.y + otherSize.y) / 2.0f - std::abs(dy);

	if (overlapX > 0 && overlapY > 0)
	{
		Event eventOther = Event{ dae::make_sdbm_hash("ColliderEnter"), static_cast<void*>(GetOwner()) };
		other->GetOwner()->NotifyObservers(eventOther);

		Event eventThis = Event{ dae::make_sdbm_hash("ColliderEnter"), static_cast<void*>(other->GetOwner()) };
		GetOwner()->NotifyObservers(eventThis);

		switch (other->Info.type)
		{

		case ColliderType::TopOnly:
		{
			float velocityY = m_pMovementComponent->GetVelocity().y;

			if (velocityY > 0.0f && (pos.y + size.y) > otherPos.y)
			{

				GetOwner()->SetLocalPosition({ pos.x, pos.y - overlapY,0 });
				m_pMovementComponent->MoveLimits.canDown = false;
				m_pMovementComponent->IsGrounded=true;
			}
			else
				m_pMovementComponent->IsGrounded=false;

		}
		break;

		case ColliderType::Solid:
		{
			glm::vec3 newPos = pos;

			if (overlapX < overlapY)
			{
				if (dx < 0) {
					newPos.x -= overlapX;
					m_pMovementComponent->MoveLimits.canRight = false;
				}
				else {
					newPos.x += overlapX;
					m_pMovementComponent->MoveLimits.canLeft = false;
				}
			}
			else
			{
				if (dy < 0) {
					newPos.y -= overlapY;
					m_pMovementComponent->MoveLimits.canDown = false;
					m_pMovementComponent->IsGrounded = true;
				}
				else {
					newPos.y += overlapY;
					m_pMovementComponent->MoveLimits.canUp = false;
					m_pMovementComponent->IsGrounded = false;
				}
			}

			GetOwner()->SetLocalPosition(newPos);
		}
		break;

		}

	}
}

void dae::ColliderComponent::HandleTriggerCollision(const ColliderComponent* other)
{
	if (Info.isStatic) return;

	Event event = Event{ dae::make_sdbm_hash("TriggerEnter"), static_cast<void*>(this) };
	other->GetOwner()->NotifyObservers(event);
}

