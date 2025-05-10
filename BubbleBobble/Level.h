#pragma once
#include <Scene.h>
#include <filesystem>

namespace cat
{
	class Level
	{
	public:
		Level(dae::Scene& scene);

		void LoadLevel(int idx);
		void AddLevel(const std::string& filePath);
		
	private:
		dae::Scene& m_Scene;
		std::vector<std::string> m_LevelPaths;
	};
}

