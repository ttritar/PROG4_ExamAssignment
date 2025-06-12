#include "PlayerSystem.h"

// std
#include <stdexcept>
#include <string>

void dae::PlayerSystem::RegisterPlayer(int playerIdx, dae::GameObject* player)
{
	if (playerIdx < 0 || playerIdx >= static_cast<int>(m_Players.size()))
	{
		m_Players.resize(playerIdx + 1, nullptr);
	}

	if (m_Players[playerIdx] != nullptr)
	{
		throw std::runtime_error("Player already registered at index " + std::to_string(playerIdx));
	}

	m_Players[playerIdx] = player;
}

void dae::PlayerSystem::UnregisterPlayer(int playerIdx, dae::GameObject* player)
{
	if (playerIdx < 0 || playerIdx >= static_cast<int>(m_Players.size()) || m_Players[playerIdx] != player)
	{
		throw std::runtime_error("Player not registered at index " + std::to_string(playerIdx));
	}
	m_Players[playerIdx] = nullptr;
}
