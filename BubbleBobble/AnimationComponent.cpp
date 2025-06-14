#include "AnimationComponent.h"

void cat::AnimationComponent::Update(float deltaTime)
{
    m_ElapsedTime += deltaTime;
    if (m_ElapsedTime >= FrameData.frameDuration)
    {
        m_CurrentFrame = (m_CurrentFrame + 1) % FrameData.frameCount;
        m_ElapsedTime = 0.0f;
        m_SrcRect = {
            m_CurrentFrame * FrameData.frameWidth,
            FrameData.frameHeight * FrameData.row,
            FrameData.frameWidth,
            FrameData.frameHeight
        };
        m_pTextureComponent->SrcRect=m_SrcRect;
    }
}
