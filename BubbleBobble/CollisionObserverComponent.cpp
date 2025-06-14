#include "CollisionObserverComponent.h"

#include "HealthComponent.h"
#include "Level.h"
#include "ScoreComponent.h"

#include "Presets.h"
#include "ScenePresets.h"
#include "ZenChanAIComponent.h"

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
			if (!other->GetComponent<BubbleComponent>()->HasTrapped)
			{
				other->m_pendingRemoval = true;
				BubbleComponent::TrappedEnemyType type = BubbleComponent::TrappedEnemyType::Maita;
				if (other->GetComponent<ZenChanAIComponent>()) type = BubbleComponent::TrappedEnemyType::ZenChan;


				//bubble
				auto pos = thisCollider->GetOwner()->GetLocalPosition();
				thisCollider->GetOwner()->m_pendingRemoval = true;
				bool isPlayerOne = thisCollider->GetOwner()->GetComponent<AnimationComponent>()->FrameData.row == 0 ;
				other->m_pendingRemoval = true;

				auto& scene = dae::SceneManager::GetInstance().GetActiveScene();
				BubblePreset{
					.isPlayerOne = isPlayerOne,
					.direction = {},
					.type = type
				}.SpawnBubble(scene, pos);
			}
		}
		else if (otherCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Enemy) && 
			thisCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Bubble))
		{
			if (!thisCollider->GetOwner()->GetComponent<BubbleComponent>()->HasTrapped)
			{
				thisCollider->GetOwner()->m_pendingRemoval = true;
				BubbleComponent::TrappedEnemyType type = BubbleComponent::TrappedEnemyType::Maita;
				if (thisCollider->GetOwner()->GetComponent<ZenChanAIComponent>()) type = BubbleComponent::TrappedEnemyType::ZenChan;
			
			
				//bubble
				auto pos = other->GetLocalPosition();
				bool isPlayerOne = other->GetComponent<AnimationComponent>()->FrameData.row == 0;
				other->m_pendingRemoval = true;
			
				auto& scene = dae::SceneManager::GetInstance().GetActiveScene();
				BubblePreset{
					.isPlayerOne = isPlayerOne,
					.direction = {},
					.type = type
				}.SpawnBubble(scene, pos);
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
		if (otherCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Item) &&
			thisCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player))
		{
			// random nmber between 1000 and 5000
			int randomScore = rand() % 4000 + 1000;
			thisCollider->GetOwner()->GetComponent<ScoreComponent>()->GainScore(randomScore);

			other->m_pendingRemoval = true;
			Level::TotalPickups--;

			if (Level::TotalEnemies <= 0 && Level::TotalPickups <= 0)
			{
				SwitchToNextLevel();
			}
		}


		// PLAYER - BUBBLE
		if (otherCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Bubble) &&
			thisCollider->Info.tag == static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player))
		{
			auto bubble = other->GetComponent<BubbleComponent>();
			if (!bubble->Popped)
			{
				bubble->Popped = true;
				other->m_pendingRemoval = true; 

				thisCollider->GetOwner()->GetComponent<ScoreComponent>()->GainScore(10);
				bubble->ChangeState(std::make_unique<PopState>());
				if (bubble->HasTrapped)
				{
					auto& scene = dae::SceneManager::GetInstance().GetActiveScene();
					ItemPreset().SpawnItem(scene, other->GetLocalPosition());

					--Level::TotalEnemies;
					if (Level::TotalEnemies <= 0 && Level::TotalPickups <= 0)
					{
						SwitchToNextLevel();
					}
				}
			}
		}

	}
}
