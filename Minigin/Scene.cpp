#include "Scene.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_objects)
	{
		object->Update(deltaTime);
	}

	for (auto& object : m_objects)
	{
		object->LateUpdate(deltaTime);
	}

	auto iterator = std::remove_if(m_objects.begin(), m_objects.end(),	// evrything that should be removed is put on the back of the vector
		[](const std::unique_ptr<GameObject>& object) { return object->m_pendingRemoval; });
	m_objects.erase(iterator, m_objects.end());
}

void dae::Scene::FixedUpdate(float fixedStep)
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate(fixedStep);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

