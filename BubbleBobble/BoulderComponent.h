#pragma once
#include <vec2.hpp>

#include "BaseComponent.h"

namespace cat
{
	class BoulderComponent final : public dae::BaseComponent
	{
	public:
		// CTOR & DTOR
		//-------------
		BoulderComponent(dae::GameObject& owner)
			: dae::BaseComponent(owner)
		{
			m_pMovementComponent = owner.GetComponent<dae::MovementComponent>();
			if (!m_pMovementComponent)
			{
				throw std::runtime_error("BoulderComponent requires a MovementComponent on the GameObject.");
			}
		}
		virtual ~BoulderComponent() = default;
		BoulderComponent(const BoulderComponent& other) = delete;
		BoulderComponent(BoulderComponent&& other) = delete;
		BoulderComponent& operator=(const BoulderComponent& other) = delete;
		BoulderComponent& operator=(BoulderComponent&& other) = delete;

		// METHODS
		//-------------
		void Update(float deltaTime) override
		{
			m_Lifetime += deltaTime;
			if (m_Lifetime > m_MaxLifetime)
			{
				GetOwner()->m_pendingRemoval = true;
			}

			m_pMovementComponent->Move(Direction.x,Direction.y);
		}

		glm::vec2 Direction{ 1,0 };
	private:
		float m_Lifetime = 0.f;
		const float m_MaxLifetime = 2.f;

		dae::MovementComponent* m_pMovementComponent{ nullptr };
	};
}
