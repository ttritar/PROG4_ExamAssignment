#include "ColliderComponent.h"

#include <SDL_rect.h>
#include <SDL_render.h>

#include  "CollisionSystem.h"
#include "GameObject.h"
#include "MovementComponent.h"
#include "Renderer.h"
#include <iostream>

cat::ColliderComponent::ColliderComponent(dae::GameObject& owner, ColliderInfo colliderInfo)
	:BaseComponent(owner),
	m_ColliderInfo(colliderInfo)
{
	CollisionSystem::GetInstance().AddCollider(this);

	if (!m_ColliderInfo.isStatic)
	{
		m_pMovementComponent = GetOwner()->GetComponent<MovementComponent>();
	}
}

cat::ColliderComponent::~ColliderComponent()
{
	CollisionSystem::GetInstance().RemoveCollider(this);
}


void cat::ColliderComponent::Update(float)
{
	if (m_ColliderInfo.isStatic) return;

	auto colliders = CollisionSystem::GetInstance().GetColliders();

	for (auto& coll : colliders)
	{

		if (coll == this) continue;
		if (CheckCollision(coll))
		{
			ResolveCollision(coll);
		}
	}
}

void cat::ColliderComponent::Render() const
{
	DebugRendering();
}

void cat::ColliderComponent::DebugRendering() const
{
	if (!m_IsDebugRendering)return;

	auto sdlRenderer = dae::Renderer::GetInstance().GetSDLRenderer();
	SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, 1);
	if (m_ColliderInfo.type == ColliderType::TopOnly)SDL_SetRenderDrawColor(sdlRenderer, 255, 100, 0, 1);

	const SDL_Rect rect = SDL_Rect{
		static_cast<int> (GetOwner()->GetLocalPosition().x + m_ColliderInfo.offset.x),
		static_cast<int> (GetOwner()->GetLocalPosition().y + m_ColliderInfo.offset.y),
		static_cast<int> (m_ColliderInfo.size.x),
		static_cast<int> (m_ColliderInfo.size.y)
	};
	SDL_RenderDrawRect(sdlRenderer, &rect);
}


bool cat::ColliderComponent::CheckCollision(const ColliderComponent* other) const
{
	glm::vec2 pos = glm::vec2{ GetOwner()->GetLocalPosition().x,GetOwner()->GetLocalPosition().y } + m_ColliderInfo.offset;
	glm::vec2 otherPos = glm::vec2{ other->GetOwner()->GetLocalPosition().x,other->GetOwner()->GetLocalPosition().y } + other->m_ColliderInfo.offset;

	return (
		pos.x < otherPos.x + other->m_ColliderInfo.size.x &&
		pos.x + m_ColliderInfo.size.x > otherPos.x &&
		pos.y < otherPos.y + other->m_ColliderInfo.size.y &&
		pos.y + m_ColliderInfo.size.y > otherPos.y
		);
}

void cat::ColliderComponent::ResolveCollision(const ColliderComponent* other) const
{
	if (m_ColliderInfo.isStatic || !m_pMovementComponent) return;

	const glm::vec3 pos = GetPosition();
	const glm::vec2 size = GetSize();
	const glm::vec3 otherPos = other->GetPosition();
	const glm::vec2 otherSize = other->GetSize();

	float dx = (pos.x + size.x / 2.0f) - (otherPos.x + otherSize.x / 2.0f);
	float dy = (pos.y + size.y / 2.0f) - (otherPos.y + otherSize.y / 2.0f);
	float overlapX = (size.x + otherSize.x) / 2.0f - std::abs(dx);
	float overlapY = (size.y + otherSize.y) / 2.0f - std::abs(dy);

	if (overlapX > 0 && overlapY > 0)
	{
		switch (other->m_ColliderInfo.type)
		{
		case ColliderType::TopOnly:
			{
				float velocityY = m_pMovementComponent->GetVelocity().y;

				if (velocityY <= 0.0f || (pos.y + size.y) < otherPos.y)
					break;
			}

		case ColliderType::Solid:
			{
				glm::vec3 newPos = pos;

				if (overlapX < overlapY)
				{
					if (dx < 0){
						newPos.x -= overlapX;
						m_pMovementComponent->MoveLimits.right = false;
					}
					else{
						newPos.x += overlapX;
						m_pMovementComponent->MoveLimits.left = false;
					}
				}
				else
				{
					if (dy < 0){
						newPos.y -= overlapY;
						m_pMovementComponent->MoveLimits.down = false;
						m_pMovementComponent->SetIsGrounded(true);
					}
					else{
						newPos.y += overlapY;
						m_pMovementComponent->MoveLimits.up = false;
					}
				}

				GetOwner()->SetLocalPosition(newPos);
			}
			break;

		case ColliderType::Trigger:
			{
				
			}
			break;

		}
		
	}
}
