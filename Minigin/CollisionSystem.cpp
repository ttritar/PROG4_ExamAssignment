#include "CollisionSystem.h"

#include "ColliderComponent.h"



void dae::CollisionSystem::AddCollider(ColliderComponent* collider)
{
	if (collider->Info.type == ColliderComponent::ColliderType::Trigger)
	{
		m_TriggerColliders.push_back(collider);
	}
	else
	{
		m_PhysicsColliders.push_back(collider);
	}
}

void dae::CollisionSystem::RemoveCollider(ColliderComponent* collider)
{
	if (collider->Info.type == ColliderComponent::ColliderType::Trigger)
	{
		if (m_TriggerColliders.empty())return;
		auto it = std::remove(m_TriggerColliders.begin(), m_TriggerColliders.end(), collider);
		m_TriggerColliders.erase(it, m_TriggerColliders.end());
	}
	else
	{
		if (m_PhysicsColliders.empty())return;
		auto it = std::remove(m_PhysicsColliders.begin(), m_PhysicsColliders.end(), collider);
		m_PhysicsColliders.erase(it, m_PhysicsColliders.end());
	}
}
