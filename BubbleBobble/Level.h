#pragma once
#include <Scene.h>
#include <filesystem>

namespace cat
{
	class Level
	{
	public:
		Level(dae::Scene& scene, int levelNr, const std::string& filePath);
		void LoadLevel();
		
	private:
		dae::Scene& m_Scene;
		const std::string m_LevelPath;
	};
}

