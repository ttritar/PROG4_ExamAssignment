#include "HealthComponent.h"
#include "GameObject.h"
#include <iostream>

void dae::HealthComponent::TakeDamage(int damageAmount)
{
	 m_currentHealth -= damageAmount;

	 if (m_currentHealth <= 0)
	 {
		 m_currentHealth = 0;
	 }

	 Event e(make_sdbm_hash("PlayerDied"));
	 GetOwner()->NotifyObservers(e);
}
