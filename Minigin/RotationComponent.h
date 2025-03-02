#pragma once
#include "GameObject.h"

namespace dae
{
	class RotationComponent final : public BaseComponent
	{
	public:
		void Update(float deltaTime) override;

		RotationComponent(std::shared_ptr<dae::GameObject> owner, float speed, float radius)
			:BaseComponent(*owner) , m_radius(radius), m_speed(speed)
		{
		};

		virtual ~RotationComponent() = default;
		RotationComponent(const RotationComponent& other) = delete;
		RotationComponent(RotationComponent&& other) = delete;
		RotationComponent& operator=(const RotationComponent& other) = delete;
		RotationComponent& operator=(RotationComponent&& other) = delete;

	private:
		float m_radius;
		float m_speed;
		float m_elapsedSec=0;
	};
}
