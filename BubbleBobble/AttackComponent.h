#pragma once
#include <iostream>

#include "MovementComponent.h"

namespace cat
{
	class AttackComponent final : public dae::BaseComponent
	{
	public:
		enum AttackType
		{
			Bubble,
			Boulder
		};

		// CTOR & DTOR
		//-------------
		AttackComponent(dae::GameObject& owner, bool isPlayerOne, const AttackType& type = Bubble );

		virtual ~AttackComponent() = default;
		AttackComponent(const AttackComponent& other) = delete;
		AttackComponent(AttackComponent&& other) = delete;
		AttackComponent& operator=(const AttackComponent& other) = delete;
		AttackComponent& operator=(AttackComponent&& other) = delete;

		// METHODS
		//-------------
		void Attack();

	private:
		dae::MovementComponent* m_pMovementComponent{ nullptr };
		bool m_IsPlayerOne{ false };
		AttackType m_AttackType{ AttackType::Bubble };
	};
}
