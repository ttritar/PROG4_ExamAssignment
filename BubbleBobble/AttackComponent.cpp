#include "AttackComponent.h"

#include "Presets.h"

cat::AttackComponent::AttackComponent(dae::GameObject& owner, bool isPlayerOne)
	: BaseComponent(owner), m_IsPlayerOne(isPlayerOne)
{
	m_pMovementComponent = owner.GetComponent<MovementComponent>();
	if (!m_pMovementComponent)
	{
		throw std::runtime_error("AttackComponent requires a MovementComponent on the GameObject.");
	}
}

void cat::AttackComponent::Attack()
{
	cat::BubblePreset bubblePreset = {
		m_IsPlayerOne,
		m_pMovementComponent->GetDirection(),
	};
	bubblePreset.SpawnBubble(dae::SceneManager::GetInstance().GetActiveScene(), GetOwner()->GetWorldPosition());
}
