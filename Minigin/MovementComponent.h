#pragma once
#include "GameObject.h"
#include "BaseComponent.h"
#include <memory>


namespace dae
{
	class MovementComponent final : public BaseComponent
	{
	public:
		void Update(float ) override;

		MovementComponent(std::shared_ptr<dae::GameObject> owner, float speed)
			:BaseComponent(*owner), m_speed(speed)
		{
		};

		virtual ~MovementComponent() = default;
		MovementComponent(const MovementComponent& other) = delete;
		MovementComponent(MovementComponent&& other) = delete;
		MovementComponent& operator=(const MovementComponent& other) = delete;
		MovementComponent& operator=(MovementComponent&& other) = delete;


		void SetSpeed(const float speed);
		void Move(float dx, float dy);

	private:
		float m_speed;
	};

}