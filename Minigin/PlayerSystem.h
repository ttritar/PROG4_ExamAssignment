#pragma once
#include <unordered_map>
#include <xstring>

#include "GameObject.h"

namespace dae
{
	class PlayerSystem
	{
	public:
		void RegisterPlayer(const std::string& sceneName, int playerIdx, dae::GameObject* player);
		void UnregisterPlayer(const std::string& sceneName, int playerIdx, dae::GameObject* player);

		std::vector<dae::GameObject*> GetPlayers(const std::string& sceneName);
		dae::GameObject* GetPlayer(const std::string& sceneName, int playerIdx) const;

	private:
		std::unordered_map<std::string, std::vector<GameObject*>> m_ScenePlayers;
	};
}
