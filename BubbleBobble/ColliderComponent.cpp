#include "ColliderComponent.h"

#include <SDL_rect.h>
#include <SDL_render.h>

#include  "CollisionSystem.h"
#include "GameObject.h"
#include "Renderer.h"
#include <MovementCommand.h>

namespace dae
{
	ColliderComponent::ColliderComponent(std::shared_ptr<dae::GameObject> owner, ColliderInfo colliderInfo)
		:BaseComponent(*owner),
		m_ColliderInfo(colliderInfo)
	{
		CollisionSystem::GetInstance().AddCollider(this);

		if (!m_ColliderInfo.isStatic)
		{
			m_pMovementComponent = GetOwner()->GetComponent<MovementComponent>();
		}
	}

	ColliderComponent::~ColliderComponent()
	{
		CollisionSystem::GetInstance().RemoveCollider(this);
	}


	void ColliderComponent::Update(float)
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

	void ColliderComponent::Render() const
	{
		DebugRendering();
	}

	void ColliderComponent::DebugRendering() const
	{
		if (!m_IsDebugRendering)return;

		auto sdlRenderer = Renderer::GetInstance().GetSDLRenderer();
		SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, 1);
		if (m_ColliderInfo.type==ColliderType::TopOnly)SDL_SetRenderDrawColor(sdlRenderer, 255, 100, 0, 1);

		const SDL_Rect rect = SDL_Rect{
			static_cast<int> (GetOwner()->GetLocalPosition().x + m_ColliderInfo.offset.x),
			static_cast<int> (GetOwner()->GetLocalPosition().y + m_ColliderInfo.offset.y),
			static_cast<int> (m_ColliderInfo.size.x),
			static_cast<int> (m_ColliderInfo.size.y)
		};
		SDL_RenderDrawRect(sdlRenderer, &rect);
	}


	bool ColliderComponent::CheckCollision(const ColliderComponent* other) const
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

	void ColliderComponent::ResolveCollision(const ColliderComponent* other) const
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
			// TopOnly collision
			//-----------------
			if (other->m_ColliderInfo.type == ColliderType::TopOnly)
			{
				float velocityY = m_pMovementComponent->GetVelocity().y;

				if (velocityY <= 0.0f || (pos.y + size.y) < otherPos.y)
					return; 
			}


			// Solid collision
			//-----------------
			glm::vec3 newPos = pos;

			if (overlapX < overlapY)
			{
				newPos.x += (dx < 0 ? -overlapX : overlapX);
				if (m_pMovementComponent) m_pMovementComponent->SetVelocityX(0.0f); // Stop hor movement
			}
			else
			{
				newPos.y += (dy < 0 ? -overlapY : overlapY);
				if (m_pMovementComponent)
				{
					m_pMovementComponent->SetVelocityY(0.0f); // Stop vert movement
					m_pMovementComponent->SetIsGrounded(true); // Set grounded
				}
				
			}

			GetOwner()->SetLocalPosition(newPos);
		}
	}

}
