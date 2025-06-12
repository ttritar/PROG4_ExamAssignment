#pragma once
#include <vector>

namespace dae
{
	class ColliderComponent;

	class CollisionSystem
	{
	public:
		std::vector<ColliderComponent*> GetPhysicsColliders() const { return m_PhysicsColliders; }
		std::vector<ColliderComponent*> GetTriggerColliders() const { return m_TriggerColliders; }
		void AddCollider(ColliderComponent* collider);
		void RemoveCollider(ColliderComponent* collider);
		void ClearColliders()
		{
			m_PhysicsColliders.clear();
			m_TriggerColliders.clear();
		}

	private:

		std::vector<ColliderComponent*> m_PhysicsColliders{};
		std::vector<ColliderComponent*> m_TriggerColliders{}; 
	};	
}
