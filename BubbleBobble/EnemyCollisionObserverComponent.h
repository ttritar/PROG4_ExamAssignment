#pragma once
#include "Observer.h"

#include "GameObject.h"
#include "ColliderComponent.h"


namespace cat
{
	class EnemyCollisionObserverComponent final : public dae::BaseComponent, public dae::Observer
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


				// PLAYER - ENEMY
				if (otherCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player) &&
					thisCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Enemy))
				{
					other->m_pendingRemoval = true;
				}
				else if (otherCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Enemy) &&
					thisCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player))
				{
					thisCollider->GetOwner()->m_pendingRemoval = true;
				}


				// PROJECTILE - ENEMY
				if (otherCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Projectile) &&
					thisCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Enemy))
				{
					other->m_pendingRemoval = true;
					thisCollider->GetOwner()->m_pendingRemoval = true;
				}
				else if (otherCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Enemy) &&
					thisCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player))
				{
					thisCollider->GetOwner()->m_pendingRemoval = true;
					other->m_pendingRemoval = true;
				}

			}
		}

		// CTOR & DTOR
		//--------------
		EnemyCollisionObserverComponent(dae::GameObject& owner)
			: BaseComponent(owner)
		{
			// No initialization needed
		};
		virtual ~EnemyCollisionObserverComponent() = default;
		EnemyCollisionObserverComponent(const EnemyCollisionObserverComponent& other) = delete;
		EnemyCollisionObserverComponent(EnemyCollisionObserverComponent&& other) = delete;
		EnemyCollisionObserverComponent& operator=(const EnemyCollisionObserverComponent& other) = delete;
		EnemyCollisionObserverComponent& operator=(EnemyCollisionObserverComponent&& other) = delete;

	};
}