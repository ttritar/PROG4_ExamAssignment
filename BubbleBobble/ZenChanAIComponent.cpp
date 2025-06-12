#include "ZenChanAIComponent.h"

void cat::ZenChanAIComponent::Update(float deltaTime)
{
	// update target if someone else is closer
	for (auto player : m_pPlayers)
	{	// if the target and enemy are on the same level .._> add small treshold for y distance
		if (player->GetWorldPosition().y + 5.0f >= this->GetOwner()->GetWorldPosition().y &&
			player->GetWorldPosition().y - 5.0f <= this->GetOwner()->GetWorldPosition().y)
		{
			m_pTarget = player;
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
		if (!m_pTarget) m_pTarget = player;
	}

	//// set the target to the closest player
	//float oldDist = glm::distance(m_pTarget->GetWorldPosition(), GetOwner()->GetWorldPosition());
	//float newDist = glm::distance(player->GetWorldPosition(), GetOwner()->GetWorldPosition());
	//if (newDist < oldDist)
	//{
	//	m_pTarget = player;
	//}

}
