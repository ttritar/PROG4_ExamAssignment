#pragma once
#include "MovementComponent.h"

namespace cat
{
	class AttackComponent final : public dae::BaseComponent
	{
	public:
		// CTOR & DTOR
		//-------------
		AttackComponent(dae::GameObject& owner, bool isBobblon);

		virtual ~AttackComponent() = default;
		AttackComponent(const AttackComponent& other) = delete;
		AttackComponent(AttackComponent&& other) = delete;
		AttackComponent& operator=(const AttackComponent& other) = delete;
		AttackComponent& operator=(AttackComponent&& other) = delete;

		// METHODS
		//-------------
		void Attack();

	private:
		MovementComponent* m_pMovementComponent{ nullptr };
		bool m_IsBobblon{ false };
	};
}
