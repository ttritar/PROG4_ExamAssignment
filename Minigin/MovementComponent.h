#pragma once
#include "GameObject.h"
#include "BaseComponent.h"

#include "TextureComponent.h"


namespace dae
{
	class MovementComponent final : public dae::BaseComponent
	{
	public:
		// CTORS & DTORS
		//---------------
		MovementComponent(dae::GameObject& owner, float moveSpeed = 0, float jumpSpeed = 0)
			:BaseComponent(owner), m_Speed(moveSpeed), m_JumpSpeed(jumpSpeed)
		{
			m_pTextureComponent = owner.GetComponent<dae::TextureComponent>(); // is ok if it doesnt have ig, just always check
		}
		virtual ~MovementComponent() = default;
		MovementComponent(const MovementComponent& other) = delete;
		MovementComponent(MovementComponent&& other) = delete;
		MovementComponent& operator=(const MovementComponent& other) = delete;
		MovementComponent& operator=(MovementComponent&& other) = delete;

		// Methods
		//---------------
		void Update(float deltaTime) override;
		void Move(float dx, float dy);
		void Jump();

		// Getters & Setters
		void SetSpeed(float speed) { m_Speed = speed; }
		void SetJumpSpeed(float jumpSpeed) { m_JumpSpeed = jumpSpeed; }

		void SetUsesGravity(bool usesGravity) { m_UsesGravity = usesGravity; }
		void SetGravitationalConstant(float gravitationalConstant) { m_GravitationalConstant = gravitationalConstant; }

		glm::vec2 GetDirection() const { return m_Direction; }
		glm::vec2 GetVelocity() const { return Velocity; }


		// Public Members
		//---------------
		glm::vec2 Velocity = { 0,0 };

		bool IsGrounded = false;
		struct MoveLimits
		{
			bool canLeft = true;
			bool canRight = true;
			bool canUp = true;
			bool canDown = true;
		};
		MoveLimits MoveLimits{};

	private:
		// Private Methods
		//---------------
		void ApplyGravity();

		// Private Members
		//---------------
		float m_Speed;
		float m_JumpSpeed;

		bool m_UsesGravity = true;
		float m_GravitationalConstant = -4.f;

		glm::vec2 m_Direction = { -1,0 };

		float m_timeSinceJumpPress = FLT_MAX;
		const float m_MAX_JUMP_BUFFER = 1.f;

		TextureComponent* m_pTextureComponent = nullptr;
	};

}
