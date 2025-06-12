#pragma once
#include "GameObject.h"

namespace dae
{
	class PlayerSystem
	{
	public:
		void RegisterPlayer(int playerIdx, dae::GameObject* player);
		void UnregisterPlayer(int playerIdx, dae::GameObject* player);

		std::vector<dae::GameObject*> GetPlayers() const { return m_Players; }
		dae::GameObject* GetPlayer(int playerIdx) const
		{
			if (playerIdx < 0 || playerIdx >= static_cast<int>(m_Players.size()))
				return nullptr;
			return m_Players[playerIdx];
		}

	private:
		std::vector<dae::GameObject*> m_Players{}; 
	};
}
