#include "AttackComponent.h"

#include "Presets.h"

cat::AttackComponent::AttackComponent(std::shared_ptr<dae::GameObject> owner, bool isBobblon)
	: BaseComponent(*owner), m_IsBobblon(isBobblon)
{
	m_pMovementComponent = owner->GetComponent<MovementComponent>();
	if (!m_pMovementComponent)
	{
		throw std::runtime_error("AttackComponent requires a MovementComponent on the GameObject.");
	}
}

void cat::AttackComponent::Attack()
{
	cat::BubblePreset bubblePreset = {
		m_IsBobblon,
		m_pMovementComponent->GetDirection(),
	};
	bubblePreset.SpawnBubble(dae::SceneManager::GetInstance().GetActiveScene(), GetOwner()->GetWorldPosition());
}
