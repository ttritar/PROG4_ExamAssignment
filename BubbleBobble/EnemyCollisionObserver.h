#pragma once
#include "Observer.h"

#include "GameObject.h"
#include "ColliderComponent.h"


namespace cat
{
	class EnemyCollisionObserver final : public dae::Observer
	{
	public:
		void Notify(const dae::Event& event, dae::GameObject* pGameObject) override
		{
			if (event.id == dae::make_sdbm_hash("TriggerEnter"))
			{
				if (pGameObject->GetComponent<dae::ColliderComponent>()->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player))
				{
					pGameObject->m_pendingRemoval =true;
				}
			}
		}
	};
}