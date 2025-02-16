#include <string>

#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"


void dae::GameObject::Update(float deltaTime)
{
	for (auto& component : m_components)
	{
		component->Update(deltaTime);
	}

	auto iterator = std::remove_if(m_components.begin(), m_components.end(),	// evrything that should be removed is put on the back of the vector
		[](const std::shared_ptr<BaseComponent>& component) { return component->pendingRemove; });
	m_components.erase(iterator, m_components.end());
}

void dae::GameObject::LateUpdate(float deltaTime)
{
	for (const auto& component : m_components)
	{
		component->LateUpdate( deltaTime);
	}
}

void dae::GameObject::FixedUpdate(float fixedStep)
{
	for (const auto& component : m_components)
	{
		component->FixedUpdate(fixedStep);
	}
}

void dae::GameObject::Render() const
{

	for (const auto& component : m_components)
	{
		component->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
