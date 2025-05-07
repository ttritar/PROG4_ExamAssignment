#pragma once
#include "GameObject.h"
#include "BaseComponent.h"
#include <memory>


namespace dae
{
	class MovementComponent final : public BaseComponent
	{
	public:
		// CTORS & DTORS
		//---------------
		MovementComponent(std::shared_ptr<dae::GameObject> owner, float moveSpeed, float jumpSpeed = 0)
			:BaseComponent(*owner), m_Speed(moveSpeed), m_JumpSpeed(jumpSpeed)
		{
		};
		virtual ~MovementComponent() = default;
		MovementComponent(const MovementComponent& other) = delete;
		MovementComponent(MovementComponent&& other) = delete;
		MovementComponent& operator=(const MovementComponent& other) = delete;
		MovementComponent& operator=(MovementComponent&& other) = delete;

		// Methods
		//---------------
		void Update(float deltaTime) override;
		void Move(float dx, float dy) ;
		void Jump() ;

		// Getters & Setters
		void SetSpeed(float speed) { m_Speed = speed; }
		void SetJumpSpeed(float jumpSpeed) { m_JumpSpeed = jumpSpeed; }

		void SetVelocityX(float x) { m_Velocity.x = x; }
		void SetVelocityY(float y) { m_Velocity.y = y; }
		void SetVelocity(const glm::vec2& velocity) { m_Velocity = velocity; }
		glm::vec2 GetVelocity() const { return m_Velocity; }

		void SetIsGrounded(bool isGrounded) { m_IsGrounded = isGrounded; }

		void SetUsesGravity(bool usesGravity) { m_UsesGravity = usesGravity; }
		void SetGravitationalConstant(float gravitationalConstant) { m_GravitationalConstant = gravitationalConstant; }
	private:
		// Private Methods
		//---------------
		void ApplyGravity();

		// Private Members
		//---------------
		float m_Speed;
		float m_JumpSpeed;

		bool m_UsesGravity = true;
		float m_GravitationalConstant = -9.81f;

		glm::vec2 m_Velocity = { 0,0 };

		bool m_IsGrounded = false;
	};

}