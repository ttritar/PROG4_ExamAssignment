#pragma once
#include "Transform.h"

namespace dae
{
	class GameObject;

	class BaseComponent	// MAKE INTERFACE
	{
	public:
		virtual void Update(float ) {  };
		virtual void LateUpdate(float ) {  };
		virtual void FixedUpdate(float ) {  };
		virtual void Render() const {};



		virtual ~BaseComponent()=default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;


		bool pendingRemove = false;

	protected:
		BaseComponent(dae::GameObject& owner) { m_pOwner = &owner; };
		virtual GameObject* GetOwner() const { return m_pOwner; }

	private:
		GameObject* m_pOwner{ nullptr };	// REQUIRED
	};

}