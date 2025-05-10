#include "MaitaAIComponent.h"

void cat::MaitaAIComponent::Wander(float deltaTime)
{
    // check timer
    m_WanderTimer -= deltaTime;

    if (m_WanderTimer <= 0.f)
    {
        // goes to random direction
        m_Dx = (rand() % 2 == 0 ? 1 : -1) * 0.5f;
        m_Dy = (rand() % 2 == 0 ? 1 : -1) * 0.5f;

        // normalize 
        float magnitude = std::sqrt(m_Dx * m_Dx + m_Dy * m_Dy);

        if (magnitude > 0.0f)
        {
            m_Dx /= magnitude;
            m_Dy /= magnitude;
        }
    }

    m_MovementComponent->Move(m_Dx, m_Dy);
}

void cat::MaitaAIComponent::Chase(float )
{
    // get pos
    auto playerPosition = m_pTarget->GetWorldPosition();

	// calc direction to target
    float dx = playerPosition.x - GetOwner()->GetWorldPosition().x;
    float dy = playerPosition.y - GetOwner()->GetWorldPosition().y;

	// normalize
    float magnitude = std::sqrt(dx * dx + dy * dy);
    if (magnitude > 0.0f)
    {
        dx /= magnitude;
        dy /= magnitude;
    }

	m_MovementComponent->Move(dx, dy);
}
