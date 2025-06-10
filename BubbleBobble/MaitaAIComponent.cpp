#include "MaitaAIComponent.h"

#include "GameObject.h"


void cat::MaitaAIComponent::Update(float deltaTime)
{
	// STATE
	//-----------------
	std::unique_ptr<MaitaState> newState = nullptr;
	if (m_CurrentState)
	{
		newState = m_CurrentState->Update(deltaTime);
	}
	if (newState)
	{
		ChangeState(std::move(newState));
	}

	UpdatePlayerVisibility();
}

void cat::MaitaAIComponent::ChangeState(std::unique_ptr<MaitaState> newState)
{
	if (m_CurrentState) m_CurrentState->OnExit();
	m_CurrentState = std::move(newState);
	if (m_CurrentState) m_CurrentState->OnEnter(this);
}


void cat::MaitaAIComponent::UpdatePlayerVisibility()
{
	if (m_pPlayers.empty()) return;

	for (auto player : m_pPlayers)
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


