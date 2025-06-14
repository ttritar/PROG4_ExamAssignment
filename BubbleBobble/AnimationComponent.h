#pragma once
#include "BaseComponent.h"

// std
#include <memory>

#include "TextureComponent.h"

namespace cat
{
	class AnimationComponent : public dae::BaseComponent
	{
	public:
		struct FrameAnimationData
		{
			int frameWidth;
			int frameHeight;
			int frameCount;
			float frameDuration;

			int row = 0;
		};


		// CTOR & DTOR
		//-------------
		AnimationComponent(dae::GameObject& owner, FrameAnimationData frameData)
			:BaseComponent(owner), FrameData(frameData)
		{
			m_pTextureComponent = owner.GetComponent<dae::TextureComponent>();
			if (!m_pTextureComponent) throw std::runtime_error("AnimationComponent requires a TextureComponent to function.");

			m_SrcRect = {
				m_CurrentFrame * FrameData.frameWidth,
				FrameData.frameHeight * FrameData.row,
				FrameData.frameWidth,
				FrameData.frameHeight
			};
			m_pTextureComponent->SrcRect=m_SrcRect;
		}

		virtual ~AnimationComponent() = default;
		AnimationComponent(const AnimationComponent& other) = delete;
		AnimationComponent(AnimationComponent&& other) = delete;
		AnimationComponent& operator=(const AnimationComponent& other) = delete;
		AnimationComponent& operator=(AnimationComponent&& other) = delete;

			
		// METHODS
		//-------------
		void Update(float deltaTime) override;

		FrameAnimationData FrameData;
	private:
		// Private Methods
		//-----------------

		// Private Members
		//-----------------
		dae::TextureComponent* m_pTextureComponent;
		SDL_Rect m_SrcRect;

		int m_CurrentFrame{ 0 };
		float m_ElapsedTime{ 0.0f };

	};
}
