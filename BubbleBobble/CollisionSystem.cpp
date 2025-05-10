#include "CollisionSystem.h"
#include "ColliderComponent.h"


std::vector<cat::ColliderComponent*> cat::CollisionSystem::GetColliders() const
{
	return m_Colliders;
}

void cat::CollisionSystem::AddCollider(ColliderComponent* collider)
{
	m_Colliders.emplace_back(collider);
}

void cat::CollisionSystem::RemoveCollider(ColliderComponent* collider)
{
	if (m_Colliders.empty())return;
	auto it = std::remove(m_Colliders.begin(), m_Colliders.end(), collider);
	m_Colliders.erase(it, m_Colliders.end());
}
