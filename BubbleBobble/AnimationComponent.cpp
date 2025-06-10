#include "AnimationComponent.h"

void cat::AnimationComponent::Update(float deltaTime)
{
	m_ElapsedTime += deltaTime;
	if (m_ElapsedTime >= m_FrameData.frameDuration)
	{
		m_CurrentFrame = (m_CurrentFrame + 1) % m_FrameData.frameCount;
		m_ElapsedTime = 0.0f;
		SDL_Rect srcRect{
			m_CurrentFrame * m_FrameData.frameWidth,
			0,
			m_FrameData.frameWidth,
			m_FrameData.frameHeight
		};
		m_pTextureComponent->SetSourceRect(srcRect);
	}
}
