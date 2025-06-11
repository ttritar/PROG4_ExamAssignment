#include "SceneManager.h"
#include "Scene.h"


dae::Scene* dae::SceneManager::GetScene(const std::string& name) const
{
	for (const auto& scene : m_Scenes)
	{
		if (scene->GetName() == name)
			return scene.get();
	}
	return nullptr;
}

bool dae::SceneManager::SetActiveScene(const std::string& name)
{
	for (const auto& scene : m_Scenes)
	{
		if (scene->GetName() == name)
		{
			m_ActiveScene = scene.get();
			return true;
		}
	}
	return false;
}




void dae::SceneManager::Update(float deltaTime)
{
	if (m_ActiveScene)
		m_ActiveScene->Update(deltaTime);
}

void dae::SceneManager::FixedUpdate(float fixedStep)
{
	if (m_ActiveScene)
		m_ActiveScene->FixedUpdate(fixedStep);
}

void dae::SceneManager::Render()
{
	if (m_ActiveScene)
		m_ActiveScene->Render();
}


dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);

	if (!m_ActiveScene)
		m_ActiveScene = scene.get();

	return *scene;
}
