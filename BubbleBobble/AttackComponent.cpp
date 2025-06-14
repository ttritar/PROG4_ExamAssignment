#include "AttackComponent.h"

#include "Presets.h"

cat::AttackComponent::AttackComponent(dae::GameObject& owner, bool isPlayerOne, const AttackType& type)
	: BaseComponent(owner), m_IsPlayerOne(isPlayerOne), m_AttackType(type)
{
	m_pMovementComponent = owner.GetComponent<dae::MovementComponent>();
	if (!m_pMovementComponent)
	{
		throw std::runtime_error("AttackComponent requires a MovementComponent on the GameObject.");
	}
}

void cat::AttackComponent::Attack()
{
	if (m_AttackType == Bubble)
	{
		cat::BubblePreset bubblePreset = {
			m_IsPlayerOne,
			m_pMovementComponent->GetDirection(),
		};
		bubblePreset.SpawnBubble(dae::SceneManager::GetInstance().GetActiveScene(), GetOwner()->GetWorldPosition());

		dae::Event event{ dae::make_sdbm_hash("PlayerAttacked") };
		GetOwner()->NotifyObservers(event);
	}
	else if (m_AttackType == Boulder)
	{
		cat::BoulderPreset boulderPreset = {
			m_pMovementComponent->GetDirection(),
		};
		boulderPreset.SpawnBoulder(dae::SceneManager::GetInstance().GetActiveScene(), GetOwner()->GetWorldPosition());

		dae::Event event{ dae::make_sdbm_hash("MaitaAttacked") };
		GetOwner()->NotifyObservers(event);
	}
}
