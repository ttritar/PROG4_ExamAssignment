#include "CollisionObserverComponent.h"

#include "HealthComponent.h"
#include "Level.h"
#include "ScoreComponent.h"

#include "Presets.h"
#include "ScenePresets.h"

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
		if (otherCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Bubble) &&
			thisCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Enemy))
		{
			other->m_pendingRemoval = true;

			// bubble
			thisCollider->GetOwner()->m_pendingRemoval = true;

			auto& scene = dae::SceneManager::GetInstance().GetActiveScene();
			ItemPreset().SpawnItem(scene, other->GetLocalPosition());
			Level::TotalEnemies--;
			if (Level::TotalEnemies == 0 && Level::TotalPickups == 0)
			{
				SwitchToNextLevel();
			}
		}
		else if (otherCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Enemy) &&
			thisCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Bubble))
		{
			thisCollider->GetOwner()->m_pendingRemoval = true;

			//bubble
			other->m_pendingRemoval = true;

			auto& scene = dae::SceneManager::GetInstance().GetActiveScene();
			ItemPreset().SpawnItem(scene, thisCollider->GetOwner()->GetLocalPosition());
			Level::TotalEnemies--;
			if (Level::TotalEnemies == 0 && Level::TotalPickups == 0)
			{
				SwitchToNextLevel();
			}
		}

	}
}

void cat::PlayerCollisionObserverComponent::Notify(const dae::Event& event, dae::GameObject* object)
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
			Level::TotalPickups--;

			if (Level::TotalEnemies == 0 && Level::TotalPickups == 0)
			{
				SwitchToNextLevel();
			}
		}
		else if (otherCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Item) &&
			thisCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player))
		{
			// random nmber between 1000 and 5000
			int randomScore = rand() % 4000 + 1000;
			thisCollider->GetOwner()->GetComponent<ScoreComponent>()->GainScore(randomScore);

			other->m_pendingRemoval = true;
			Level::TotalPickups--;

			if (Level::TotalEnemies == 0 && Level::TotalPickups == 0)
			{
				SwitchToNextLevel();
			}
		}


		// PLAYER - BUBBLE

		if (otherCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player) &&
			thisCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Bubble))
		{
			otherCollider->GetOwner()->GetComponent<ScoreComponent>()->GainScore(10);
			thisCollider->GetOwner()->GetComponent<BubbleComponent>()->ChangeState(std::make_unique<PopState>());
		}
		else if (otherCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Bubble) &&
			thisCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player))
		{
			thisCollider->GetOwner()->GetComponent<ScoreComponent>()->GainScore(10);
			other->GetComponent<BubbleComponent>()->ChangeState(std::make_unique<PopState>());
		}
	}
}
