#include "HealthComponent.h"
#include "GameObject.h"
#include <algorithm>
#include <iostream>


cat::HealthComponent::HealthComponent(dae::GameObject& owner)
	:BaseComponent(owner)
{
}

void cat::HealthComponent::Update(float dt)
{
	if (m_damageCooldown > 0.f)
		m_damageCooldown -= dt;
}

void cat::HealthComponent::TakeDamage(int damageAmount)
{
	if (m_damageCooldown > 0.f)
		return;


	if (m_currentHealth == 0)
	{
		dae::Event e(dae::make_sdbm_hash("LoseGame"));
		GetOwner()->NotifyObservers(e);
	}

	m_currentHealth -= damageAmount;
	dae::Event e(dae::make_sdbm_hash("LoseHealth"));
	GetOwner()->NotifyObservers(e);


	m_damageCooldown = m_cooldownDuration;
}
