#pragma once

#include "BaseComponent.h"
#include <memory>
#include "Observer.h"


namespace dae
{
	class HealthComponent : public BaseComponent
	{
	public:
		HealthComponent(std::shared_ptr<dae::GameObject> owner,const int health)
			:BaseComponent(*owner),
			m_currentHealth(health), m_maxHealth(health)
		{
		};

		virtual ~HealthComponent() = default;
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;



		int GetCurrentHealth() { return m_currentHealth; }
		int GetMaxHealth() { return m_maxHealth; }

		void TakeDamage(int damageAmount);

	private:
		int m_currentHealth;
		const int m_maxHealth;
	};

}