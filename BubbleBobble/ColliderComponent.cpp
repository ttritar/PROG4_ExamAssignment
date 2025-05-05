#include "ColliderComponent.h"

#include <SDL_rect.h>
#include <SDL_render.h>

#include  "CollisionSystem.h"
#include "GameObject.h"
#include "Renderer.h"

namespace dae
{
    void ColliderComponent::Render() const
    {
        DebugRendering();
    }

    void ColliderComponent::DebugRendering() const
    {
		if (!m_IsDebugRendering)return;

        auto sdlRenderer = Renderer::GetInstance().GetSDLRenderer();
        SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, 1);

        const SDL_Rect rect = SDL_Rect{
            static_cast<int> (GetOwner()->GetLocalPosition().x + m_ColliderInfo.offset.x),
            static_cast<int> (GetOwner()->GetLocalPosition().y + m_ColliderInfo.offset.y),
            static_cast<int> (m_ColliderInfo.size.x),
            static_cast<int> (m_ColliderInfo.size.y)
        };
        SDL_RenderDrawRect(sdlRenderer, &rect);
    }

    ColliderComponent::ColliderComponent(std::shared_ptr<dae::GameObject> owner, ColliderInfo colliderInfo)
        :BaseComponent(*owner),
		m_ColliderInfo(colliderInfo)
    {
        CollisionSystem::GetInstance().AddCollider(this);

		if (m_ColliderInfo.isStatic)
		{
			m_pMovementComponent = nullptr;
		}
		else
		{
            m_pMovementComponent = owner->GetComponent<MovementComponent>();
		}
    }

    ColliderComponent::~ColliderComponent()
    {
        CollisionSystem::GetInstance().RemoveCollider(this);
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


}
