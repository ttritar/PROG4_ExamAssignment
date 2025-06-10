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
		struct FrameData
		{
			int frameWidth;
			int frameHeight;
			int frameCount;
			float frameDuration;

			int row = 0;
		};


		// CTOR & DTOR
		//-------------
		AnimationComponent(std::shared_ptr<dae::GameObject> owner, const FrameData& frameData)
			:BaseComponent(*owner), m_FrameData(frameData)
		{
			m_pTextureComponent = owner->GetComponent<TextureComponent>();
			if (!m_pTextureComponent) throw std::runtime_error("AnimationComponent requires a TextureComponent to function.");
			m_pTextureComponent->SetSourceRect({
				0, 0,
				m_FrameData.frameWidth,
				m_FrameData.frameHeight
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

	private:
		// Private Methods
		//-----------------

		// Private Members
		//-----------------
		FrameData m_FrameData;
		TextureComponent* m_pTextureComponent;

		int m_CurrentFrame{ 0 };
		float m_ElapsedTime{ 0.0f };

	};
}
