#pragma once
#include "Transform.h"

namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:
		virtual void Update([[maybe_unused]]float deltaTime) {};
		virtual void LateUpdate([[maybe_unused]] float deltaTime) {};
		virtual void FixedUpdate([[maybe_unused]] float fixedStep) { };
		virtual void Render() const {};


		void SetOwner(GameObject* owner) { m_owner = owner; }
		virtual void SetPosition(const float x, const float y)
		{
			m_transform.SetPosition(x, y, 0.0f);
		}


		BaseComponent()=default;
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;


		bool pendingRemove = false;
	protected:
		GameObject* m_owner{ nullptr };
		Transform m_transform{};
	};

}