#include "FPSComponent.h"


void dae::FPSComponent::Update(float deltaTime)
{
	const float updateInterval = 0.2f;

	m_elapsedSec+=deltaTime;

	if (m_elapsedSec >= updateInterval)
	{
		m_fps = 1/deltaTime;

		m_elapsedSec -= updateInterval;

		if (m_pTextComponent)
			m_pTextComponent->SetText(std::to_string(m_fps) + " FPS");
		
	}
}