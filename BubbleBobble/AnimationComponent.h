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
		AnimationComponent(dae::GameObject& owner, const FrameAnimationData& frameData)
			:BaseComponent(owner), FrameData(frameData)
		{
			m_pTextureComponent = owner.GetComponent<dae::TextureComponent>();
			if (!m_pTextureComponent) throw std::runtime_error("AnimationComponent requires a TextureComponent to function.");
			m_pTextureComponent->SetSourceRect({
				m_CurrentFrame* FrameData.frameWidth,
				FrameData.frameHeight * FrameData.row,
				FrameData.frameWidth,
				FrameData.frameHeight
				});
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

		int m_CurrentFrame{ 0 };
		float m_ElapsedTime{ 0.0f };

	};
}
