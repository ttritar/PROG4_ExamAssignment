#pragma once
#include <Scene.h>
#include <filesystem>

namespace cat
{
	class Level
	{
	public:
		enum class LevelGameMode
		{
			SinglePlayer,
			Multiplayer,
			Versus,
		};

		Level(dae::Scene& scene, int levelNr, const std::string& filePath,const LevelGameMode& gameMode);
		void LoadLevel();
		
	private:
		dae::Scene& m_Scene;
		const std::string m_LevelPath;
		LevelGameMode m_GameMode;
	};
}

