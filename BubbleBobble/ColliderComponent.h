#pragma once

#include "BaseComponent.h"

//std
#include <memory>
#include <vector>

#include "GameObject.h"

namespace dae
{
	class MovementComponent;
}

namespace dae
{
	// Simple 2D box collision system ...................... frfr

	class CollisionSystem;	

    class ColliderComponent final: public BaseComponent
    {
    public:
		struct ColliderInfo
		{
			bool isStatic;
			glm::vec2 size;
			glm::vec2 offset = { 0,0 };
		};

		// CTOR & DTOR
		//---------------
		ColliderComponent(std::shared_ptr<dae::GameObject> owner, ColliderInfo colliderInfo);
		~ColliderComponent() override;
		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;

		// Methods
		//---------------
		void Update(float deltaTime) override;
		void Render() const override;

		// Getters & Setters
		void SetDebugRendering(bool value) { m_IsDebugRendering = value; }
		bool GetIsStatic() const { return m_ColliderInfo.isStatic; }
		glm::vec3 GetPosition() const { return GetOwner()->GetLocalPosition() + glm::vec3{m_ColliderInfo.offset, 0}; }
		glm::vec2 GetSize() const { return m_ColliderInfo.size; }

	private:
		// Private Methods
		//---------------
		void DebugRendering() const;
		bool CheckCollision(const ColliderComponent* other) const;
		void ResolveCollision(const ColliderComponent* other) const;


		// Private Members
		//---------------
		bool m_IsDebugRendering{1};
		ColliderInfo m_ColliderInfo{};
		MovementComponent* m_pMovementComponent{ nullptr };
    };
}
