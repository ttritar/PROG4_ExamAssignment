#pragma once
#include <Scene.h>
#include <filesystem>

namespace dae
{
	class Level
	{
	public:
		Level(Scene& scene);

		void LoadLevel(int idx);
		void AddLevel(const std::string& filePath);
		
	private:
		Scene& m_Scene;
		std::vector<std::string> m_LevelPaths;
	};
}

