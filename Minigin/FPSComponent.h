#pragma once
#include "GameObject.h"
#include "TextComponent.h"

namespace dae
{

	class FPSComponent final : public BaseComponent
	{
	public:
		void Update(float deltaTime) override ;
		//void Render() const override;

		float GetFPS() const { return m_fps; }

		FPSComponent() = default;
		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

	private: 
		float m_fps = 0.0f;
		float m_elapsedSec = 0.0f;
	};
}
