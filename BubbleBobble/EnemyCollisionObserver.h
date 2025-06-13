#pragma once
#include "Observer.h"

#include "GameObject.h"
#include "ColliderComponent.h"


namespace cat
{
	class EnemyCollisionObserver final : public dae::Observer
	{
	public:
		void Notify(const dae::Event& event, dae::GameObject* object) override
		{
			if (event.id == dae::make_sdbm_hash("ColliderEnter"))
			{
				// TODO: FIX THIS WHOLE EVENT

				auto* other = static_cast<dae::GameObject*>(event.arg);
				if (!other || !object) return;
				auto* otherCollider = other->GetComponent<dae::ColliderComponent>();
				if (!otherCollider) return;

				auto* thisCollider = object->GetComponent<dae::ColliderComponent>();
				if (!thisCollider) return;


				//// PLAYER - ENEMY
				//if (otherCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player) &&
				//	thisCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Enemy))
				//{
				//	other->m_pendingRemoval = true;
				//}
				//else if (otherCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Enemy) &&
				//	thisCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player))
				//{
				//	thisCollider->GetOwner()->m_pendingRemoval = true;
				//}


				// PROJECTILE - ENEMY
				if (otherCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Projectile) &&
					thisCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Enemy))
				{
					other->m_pendingRemoval = true;
				}
				else if (otherCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Enemy) &&
					thisCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player))
				{
					thisCollider->GetOwner()->m_pendingRemoval = true;
				}

			}
		}
	};
}