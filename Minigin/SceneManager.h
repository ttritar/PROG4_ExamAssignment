#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		Scene& GetActiveScene() const { return *m_Scenes.back(); }
		Scene* GetScene(const std::string& name) const;
		bool SetActiveScene(const std::string& name);

		void Update(float deltaTime);
		void FixedUpdate(float fixedStep);

		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;

		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_ActiveScene{ nullptr };
	};
}
