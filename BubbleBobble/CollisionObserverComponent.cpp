#include "CollisionObserverComponent.h"

#include "HealthComponent.h"
#include "ScoreComponent.h"

#include "Presets.h"

void cat::EnemyCollisionObserverComponent::Notify(const dae::Event& event, dae::GameObject* object)
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
			other->GetComponent<HealthComponent>()->TakeDamage(1); 
		}
		else if (otherCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Enemy) &&
			thisCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player))
		{
			thisCollider->GetOwner()->GetComponent<HealthComponent>()->TakeDamage(1);
		}


		// PROJECTILE - ENEMY
		if (otherCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Projectile) &&
			thisCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Enemy))
		{
			other->m_pendingRemoval = true;

			// bubble
			thisCollider->GetOwner()->m_pendingRemoval = true;

			auto& scene = dae::SceneManager::GetInstance().GetActiveScene();
			ItemPreset().SpawnItem(scene, other->GetLocalPosition());

		}
		else if (otherCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Enemy) &&
			thisCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Projectile))
		{
			thisCollider->GetOwner()->m_pendingRemoval = true;

			//bubble
			other->m_pendingRemoval = true;

			auto& scene = dae::SceneManager::GetInstance().GetActiveScene();
			ItemPreset().SpawnItem(scene, thisCollider->GetOwner()->GetLocalPosition());
		}

	}
}

void cat::ItemCollisionObserverComponent::Notify(const dae::Event& event, dae::GameObject* object)
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


		// PLAYER - ITEM
		if (otherCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player) &&
			thisCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Item))
		{
			// random nmber between 1000 and 5000
			int randomScore = rand() % 4000 + 1000;
			thisCollider->GetOwner()->GetComponent<ScoreComponent>()->GainScore(randomScore);

			thisCollider->GetOwner()->m_pendingRemoval = true;
		}
		else if (otherCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Item) &&
			thisCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player))
		{
			// random nmber between 1000 and 5000
			int randomScore = rand() % 4000 + 1000;
			thisCollider->GetOwner()->GetComponent<ScoreComponent>()->GainScore(randomScore);

			other->m_pendingRemoval = true;
		}


	}
}
