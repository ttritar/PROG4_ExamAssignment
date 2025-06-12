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
	m_ColliderInfo(colliderInfo)
{
	ServiceLocator::GetInstance().GetCollisionSystem().AddCollider(this);

	if (!m_ColliderInfo.isStatic)
	{
		m_pMovementComponent = GetOwner()->GetComponent<cat::MovementComponent>();
	}
}

dae::ColliderComponent::~ColliderComponent()
{
	ServiceLocator::GetInstance().GetCollisionSystem().RemoveCollider(this);
}


void dae::ColliderComponent::Update(float )
{
	
}

void dae::ColliderComponent::FixedUpdate(float fixedTime)
{
	if (m_ColliderInfo.isStatic) return;
	if (!m_pMovementComponent) return;

	auto colliders = ServiceLocator::GetInstance().GetCollisionSystem().GetColliders();

	auto pos = GetOwner()->GetWorldPosition();
	auto velocity = m_pMovementComponent->GetVelocity();
	if (velocity.y < 0.01f && velocity.y > -1.01f)
		velocity.y = -9.81f; 
	//std::cout << "ColliderComponent velocity: " << velocity.x << ", " << velocity.y << std::endl;
	auto size = m_ColliderInfo.size;

	m_pMovementComponent->SetIsGrounded(false);
	for (auto& coll : colliders)
	{
		if (coll == this) continue;
		auto collPos = coll->GetOwner()->GetWorldPosition();
		auto collSize = coll->m_ColliderInfo.size;
		auto result = RectRectCollisionCheck(pos, size, velocity, collPos, collSize, fixedTime);
		if (result.hit)
		{
			//GetOwner()->SetLocalPosition({ result.position.x,result.position.y,0 });
			//std::cout << "Collision detected normal is: " << result.normal.x << ", "<< result.normal.y << std::endl;
			////std::cout << "Collision detected with: " << std::endl;
			//if (result.normal.y < 0)
			//{
			//	GetOwner()->SetLocalPosition({ pos.x, coll->GetPosition().y - size.y,0 });
			//	m_pMovementComponent->MoveLimits.down = false;
			//	m_pMovementComponent->SetIsGrounded(true);
			//}
			///*else if (result.normal.x < 0)
			//{
			//	GetOwner()->SetLocalPosition({ coll->GetPosition().x + size.x, pos.y,0 });
			//	m_pMovementComponent->MoveLimits.left = false;
			//}
			//else if (result.normal.x > 0)
			//{
			//	GetOwner()->SetLocalPosition({ coll->GetPosition().x, pos.y,0 });
			//	m_pMovementComponent->MoveLimits.right = false;
			//}*/
		}
		if (coll == this) continue;
		if (CheckCollision(coll))
		{
			ResolveCollision(coll);
		}
	}
}

void dae::ColliderComponent::DebugRendering() const
{
	auto sdlRenderer = dae::Renderer::GetInstance().GetSDLRenderer();
	SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, 1);
	if (m_ColliderInfo.type == ColliderType::TopOnly)SDL_SetRenderDrawColor(sdlRenderer, 255, 100, 0, 1);

	const SDL_Rect rect = SDL_Rect{
		static_cast<int> (GetOwner()->GetLocalPosition().x + m_ColliderInfo.offset.x),
		static_cast<int> (GetOwner()->GetLocalPosition().y + m_ColliderInfo.offset.y),
		static_cast<int> (m_ColliderInfo.size.x),
		static_cast<int> (m_ColliderInfo.size.y)
	};
}

dae::CollisionResult dae::ColliderComponent::RayRectCollisionCheck(const glm::vec2& rayOrigin, const glm::vec2& rayDirection, const glm::vec2& rectOrigin, const glm::vec2& rectSize)
{
	glm::vec2 contactNormal = { 0,0 };
	glm::vec2 contactPoint = { 0,0 };

	glm::vec2 invDir = { 1.0f / rayDirection.x, 1.0f / rayDirection.y };

	glm::vec2 timeNear;
	timeNear.x = (rectOrigin.x - rayOrigin.x) * invDir.x;
	timeNear.y = (rectOrigin.y - rayOrigin.y) * invDir.y;
	glm::vec2 timeFar;
	timeFar.x = (rectOrigin.x + rectSize.x - rayOrigin.x) * invDir.x;
	timeFar.y = (rectOrigin.y + rectSize.y - rayOrigin.y) * invDir.y;

	if (std::isnan(timeFar.y) || std::isnan(timeFar.x)) return {false};
	if (std::isnan(timeNear.y) || std::isnan(timeNear.x)) return { false };

	if (timeNear.x > timeFar.x) std::swap(timeNear.x, timeFar.x);
	if (timeNear.y > timeFar.y) std::swap(timeNear.y, timeFar.y);

	if (timeNear.x > timeFar.y || timeNear.y > timeFar.x) return {false};

	float firstTimeHit = std::max(timeNear.x, timeNear.y);

	float lastTimeHit = std::min(timeFar.x, timeFar.y);

	if (lastTimeHit < 0)
		return {false};

	contactPoint = rayOrigin + firstTimeHit * rayDirection;

	if (timeNear.x > timeNear.y)
		if (invDir.x < 0)
			contactNormal = { 1, 0 };
		else
			contactNormal = { -1, 0 };
	else if (timeNear.x < timeNear.y)
		if (invDir.y < 0)
			contactNormal = { 0, 1 };
		else
			contactNormal = { 0, -1 };

	return { true, firstTimeHit, contactPoint, contactNormal };

}

dae::CollisionResult dae::ColliderComponent::RectRectCollisionCheck(const glm::vec2& rect1Origin, const glm::vec2& rect1Size,const glm::vec2& rect1Velocity, const glm::vec2& rect2Origin, const glm::vec2& rect2Size, float deltaTime)
{
	if (rect1Velocity.x == 0 && rect1Velocity.y == 0)
		return {false};

	glm::vec2 expandedRect2Pos = rect2Origin - rect1Size/2.f;
	glm::vec2 expandedRect2Size = rect2Size + rect1Size;

	CollisionResult result = RayRectCollisionCheck(rect1Origin + rect1Size / 2.f, rect1Velocity * deltaTime, expandedRect2Pos, expandedRect2Size);

	if (!result.hit)
		return { false };

	if ((result.time >= 0.0f && result.time < 1.0f))
	{
		return result;
	}

	return {false};
}


bool dae::ColliderComponent::CheckCollision(const ColliderComponent* other) const
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

void dae::ColliderComponent::ResolveCollision(const ColliderComponent* other) const
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

				if (velocityY > 0.0f && (pos.y + size.y) > otherPos.y)
				{

					GetOwner()->SetLocalPosition({ pos.x, pos.y - overlapY,0 });
					m_pMovementComponent->MoveLimits.down = false;
					m_pMovementComponent->SetIsGrounded(true);
				}
				else
					m_pMovementComponent->SetIsGrounded(false);

			}
			break;
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
						m_pMovementComponent->SetIsGrounded(false);
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
