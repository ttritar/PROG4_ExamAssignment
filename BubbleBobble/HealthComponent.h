#pragma once

#include "BaseComponent.h"
#include <memory>
#include "Observer.h"


namespace cat
{
	class HealthComponent : public dae::BaseComponent
	{
	public:
		HealthComponent(dae::GameObject& owner);

		virtual ~HealthComponent() = default;
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;


		void Update(float) override;

		static int GetCurrentHealth() { return m_currentHealth; }
		int GetMaxHealth() { return m_maxHealth; }

		void TakeDamage(int damageAmount);

	private:
		static inline int m_currentHealth = 4;
		const int m_maxHealth = 4;

		float m_damageCooldown = 0.f; 
		const float m_cooldownDuration = 1.f;
	};

}