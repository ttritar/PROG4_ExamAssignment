#include "EnemyAIComponent.h"

#include "GameObject.h"

cat::EnemyAIComponent::EnemyAIComponent(std::shared_ptr<dae::GameObject> owner)
	:BaseComponent(*owner)
{
	m_CurrentState = std::make_unique<WanderingState>();
}


void cat::EnemyAIComponent::Update(float deltaTime)
{
	if (m_CurrentState)
	{
		m_CurrentState->Update(*this, deltaTime);
	}

	UpdatePlayerVisibility();
}

void cat::EnemyAIComponent::ChangeState(std::unique_ptr<EnemyState> newState)
{
	if (m_CurrentState) m_CurrentState->OnExit(*this);
	m_CurrentState = std::move(newState);
	if (m_CurrentState) m_CurrentState->OnEnter(*this);
}


void cat::EnemyAIComponent::UpdatePlayerVisibility()
{
	if (m_pPlayers.empty()) return;

	for (auto player: m_pPlayers)
	{
		if (player == nullptr) continue;

		glm::vec3 playerPos = player->GetWorldPosition();
		glm::vec3 enemyPos = GetOwner()->GetWorldPosition();

		float distance = glm::distance(playerPos, enemyPos);
		if (distance < m_DetectionRadius) 
		{
			m_IsPlayerSeen = true;
			m_pTarget = player;
			return;
		}

		m_IsPlayerSeen = false;
	}
}


