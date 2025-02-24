#pragma once
#include "GameObject.h"

namespace dae
{
	class RotationComponent final : public BaseComponent
	{
	public:
		void Update(float deltaTime) override;

		RotationComponent(std::shared_ptr<dae::GameObject> owner, float radiansPerSec, float radius)
			:BaseComponent(*owner) , m_radius(radius), m_radiansPerSec(radiansPerSec)
		{
		};

		virtual ~RotationComponent() = default;
		RotationComponent(const RotationComponent& other) = delete;
		RotationComponent(RotationComponent&& other) = delete;
		RotationComponent& operator=(const RotationComponent& other) = delete;
		RotationComponent& operator=(RotationComponent&& other) = delete;

	private:
		float m_radius;
		float m_radiansPerSec;
		float m_elapsedSec=0;
	};
}
