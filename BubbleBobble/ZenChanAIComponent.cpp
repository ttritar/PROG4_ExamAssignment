#include "ZenChanAIComponent.h"

void cat::ZenChanAIComponent::Update(float deltaTime)
{
	// target reset
	m_pTarget = nullptr;

	// update target if someone else is closer
	for (auto player : m_pPlayers)
	{
		const float playerY = player->GetWorldPosition().y;
		const float zenchanY = this->GetOwner()->GetWorldPosition().y;

		// if the target and enemy are on the same level 
		if (std::abs(playerY - zenchanY) <= 5.0f)
		{
			m_pTarget = player;
			break;
		}
	}

	// STATE
	//-----------------
	std::unique_ptr<ZenChanState> newState = nullptr;
	if (m_CurrentState)
	{
		newState = m_CurrentState->Update(deltaTime);
	}
	if (newState)
	{
		ChangeState(std::move(newState));
	}

}

void cat::ZenChanAIComponent::ChangeState(std::unique_ptr<ZenChanState> newState)
{
	if (m_CurrentState) m_CurrentState->OnExit();
	m_CurrentState = std::move(newState);
	if (m_CurrentState) m_CurrentState->OnEnter(this);
}

void cat::ZenChanAIComponent::AddPlayer(dae::GameObject* player)
{
	if (player == nullptr) return;

	if (std::find(m_pPlayers.begin(), m_pPlayers.end(), player) == m_pPlayers.end())
	{
		m_pPlayers.push_back(player);
	}
}
