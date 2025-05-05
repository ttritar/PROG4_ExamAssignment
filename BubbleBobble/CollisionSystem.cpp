#include "CollisionSystem.h"
#include "ColliderComponent.h"

namespace dae
{
	void CollisionSystem::AddCollider(ColliderComponent* collider)
	{
		if (collider->GetIsStatic())
			m_StaticColliders.emplace_back(collider);
		else
			m_DynamicColliders.emplace_back(collider);
	}

	void CollisionSystem::RemoveCollider(ColliderComponent* collider)
	{
		if (collider->GetIsStatic())
		{
			auto it = std::remove(m_StaticColliders.begin(), m_StaticColliders.end(), collider);
			m_StaticColliders.erase(it, m_StaticColliders.end());
		}
		else
		{
			auto it = std::remove(m_DynamicColliders.begin(), m_DynamicColliders.end(), collider);
			m_DynamicColliders.erase(it, m_DynamicColliders.end());
		}
	}


	void CollisionSystem::DetectCollisions()
	{
		// CHECK DYNAMIC vs STATIC COLLISIONS
		//------------------
		for (ColliderComponent* dynamicCollider : m_DynamicColliders) 
		{
			for (ColliderComponent* staticCollider : m_StaticColliders)
			{
				if (dynamicCollider->CheckCollision(staticCollider)) 
				{
					ResolveCollisions(dynamicCollider, staticCollider);
				}
			}
		}


		// CHECK DYNAMIC vs DYNAMIC COLLISIONS
		//------------------
		for (size_t i = 0; i < m_DynamicColliders.size(); ++i)
		{
			for (size_t j = i + 1; j < m_DynamicColliders.size(); ++j)
			{
				if (m_DynamicColliders[i]->CheckCollision(m_DynamicColliders[j]))
				{
					ResolveDynamicCollisions(m_DynamicColliders[i],m_DynamicColliders[j]);
				}
			}
		}
	}


	void CollisionSystem::ResolveCollisions(ColliderComponent* dyn, ColliderComponent* stat)
	{
		const glm::vec3 dynPos = dyn->GetPosition();
		const glm::vec2 dynSize = dyn->GetSize();
		const glm::vec3 statPos = stat->GetPosition();
		const glm::vec2 statSize = stat->GetSize();


		float dx = (dynPos.x + dynSize.x / 2.0f) - (statPos.x + statSize.x / 2.0f);
		float dy = (dynPos.y + dynSize.y / 2.0f) - (statPos.y + statSize.y / 2.0f);
		float overlapX = (dynSize.x + statSize.x) / 2.0f - std::abs(dx);
		float overlapY = (dynSize.y + statSize.y) / 2.0f - std::abs(dy);

		if (overlapX > 0 && overlapY > 0)
		{
			if (overlapX < overlapY)
			{
				dyn->Move( dx < 0 ? -overlapX : overlapX, 0 );
			}
			else
			{
				dyn->Move( 0, dy < 0 ? -overlapY : overlapY );
			}
		}
	}

	void CollisionSystem::ResolveDynamicCollisions(ColliderComponent* ,  ColliderComponent* )
	{
	}
}
