#pragma once
#include <vector>

#include "Singleton.h"

namespace dae
{
	class ColliderComponent;

	class CollisionSystem : public Singleton<CollisionSystem>
	{
	public:
		void AddCollider(ColliderComponent* collider);
		void RemoveCollider(ColliderComponent* collider);
		void ClearColliders() { m_StaticColliders.clear(); m_DynamicColliders.clear(); }

		void DetectCollisions();

	private:
		static void ResolveCollisions(ColliderComponent* dyn, ColliderComponent* stat);
		void ResolveDynamicCollisions(ColliderComponent* col1, ColliderComponent* col2);

		std::vector<ColliderComponent*> m_StaticColliders{};
		std::vector<ColliderComponent*> m_DynamicColliders{};
	};	
}
