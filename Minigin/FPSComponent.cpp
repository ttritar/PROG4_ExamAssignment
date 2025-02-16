#include "FPSComponent.h"


void dae::FPSComponent::Update(float deltaTime)
{
	const float updateInterval = 0.2f;

	m_elapsedSec+=deltaTime;

	if (m_elapsedSec >= updateInterval)
	{
		m_fps = 1/deltaTime;

		m_elapsedSec = 0.0f;

		if (m_owner)
		{
			TextComponent* texComp = m_owner->GetComponent<TextComponent>();
			if (texComp)
				texComp->SetText(std::to_string(m_fps) + " FPS");
		}
	}
}