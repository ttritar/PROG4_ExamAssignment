#include "PlayerSystem.h"

// std
#include <stdexcept>
#include <string>

void dae::PlayerSystem::RegisterPlayer(const std::string& sceneName, int playerIdx, GameObject* player)
{
	auto& players = m_ScenePlayers[sceneName];
	if (playerIdx >= static_cast<int>(players.size()))
		players.resize(playerIdx + 1, nullptr);

	if (players[playerIdx] != nullptr)
		throw std::runtime_error("Player already registered at index " + std::to_string(playerIdx));

	players[playerIdx] = player;
}

void dae::PlayerSystem::UnregisterPlayer(const std::string& sceneName, int playerIdx, GameObject* player)
{
	auto it = m_ScenePlayers.find(sceneName);
	if (it == m_ScenePlayers.end() || it->second[playerIdx] != player)
		throw std::runtime_error("Player not registered at index " + std::to_string(playerIdx));

	it->second[playerIdx] = nullptr;
}

std::vector<dae::GameObject*> dae::PlayerSystem::GetPlayers(const std::string& sceneName)
{
	auto it = m_ScenePlayers.find(sceneName);
	if (it != m_ScenePlayers.end())
		return it->second;
	return {};
}

dae::GameObject* dae::PlayerSystem::GetPlayer(const std::string& sceneName, int playerIdx) const
{
	auto it = m_ScenePlayers.find(sceneName);
	if (it == m_ScenePlayers.end() || playerIdx >= static_cast<int>(it->second.size()))
		return nullptr;
	return it->second[playerIdx];
}