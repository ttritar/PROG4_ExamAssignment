#pragma once
#include <memory>
#include <vector>

#include "Transform.h"
#include "BaseComponent.h"



namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:
		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;


		// Datamember functions
		//------------------

		void AddComponent(std::shared_ptr<BaseComponent> component) {
			m_components.push_back(component);
			component->SetOwner(this);
		}
		template <typename T>
		void RemoveComponent(int index = 0) {
			int idx = 0;

			if (m_components.size() == 0)
				return;

			for (auto& component : m_components)
			{
				if (auto* castedComponent = dynamic_cast<T*>(component.get()))
				{
					if (idx == index)
						castedComponent->pendingRemove = true;
					++idx;

					if (idx >= m_components.size())
						break;
				}
			}
		}
		template <typename T>
		void RemoveAllComponents()	// Removes all components of type T
		{
			if (m_components.size() == 0)
				return;

			for (const auto& component : m_components)
			{
				if (auto* castedComponent = dynamic_cast<T*>(component.get()))
				{
					castedComponent->pendingRemove = true;
				}
			}
		}
		template <typename T>
		T* GetComponent(int index = 0){
			int idx = 0;

			if (m_components.size() == 0)
				return nullptr;

			for (const auto& component : m_components)
			{
				if (auto* castedComponent = dynamic_cast<T*>(component.get()))
				{
					if (idx == index)
						return castedComponent;
					++idx;

					if (idx >= m_components.size())
						break;
				}
			}

			return nullptr;
		}
		template <typename T>
		bool CheckComponentAdded()
		{
			for (const auto& component : m_components)
			{
				if (auto* castedComponent = dynamic_cast<T*>(component.get()))
				{
					return true;
				}
			}

			return false;
		}

		void Update(float deltaTime);
		void LateUpdate(float deltaTime);
		void FixedUpdate(float fixedStep);
		void Render() const;

		void SetPosition(float x, float y);


		bool pendingRemove = false;
	private:
		Transform m_transform{};

		std::vector<std::shared_ptr<BaseComponent>> m_components{};

	};
}
