#pragma once
#include <vector>

#include "Singleton.h"

namespace cat
{
	class ColliderComponent;

	class CollisionSystem : public dae::Singleton<CollisionSystem>
	{
	public:
		std::vector<ColliderComponent*> GetColliders()const;
		void AddCollider(ColliderComponent* collider);
		void RemoveCollider(ColliderComponent* collider);
		void ClearColliders() { m_Colliders.clear(); }

	private:

		std::vector<ColliderComponent*> m_Colliders{};
	};	
}
