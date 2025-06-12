#pragma once

#include "BaseComponent.h"
#include "GameObject.h"

//std


namespace cat
{
	class MovementComponent;
}

namespace dae
{
	struct CollisionResult
	{
		bool hit{ false };
		float time{ 0.0f };
		glm::vec2 position{ 0.0f, 0.0f };
		glm::vec2 normal{ 0.0f, 0.0f };
	};

	// swept AABB 
    class ColliderComponent final: public dae::BaseComponent
    {
    public:
	    enum class ColliderType
	    {
		    Solid=0,
			TopOnly=1,
			Trigger=2
	    };

		struct ColliderInfo
		{
			ColliderType type = ColliderType::Solid;
			bool isStatic;
			glm::vec2 size;
			glm::vec2 offset = { 0,0 };
		};

		// CTOR & DTOR
		//---------------
	    ColliderComponent(dae::GameObject& owner, ColliderInfo colliderInfo);
		~ColliderComponent() override;

		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;

		// Methods
		//---------------
		void Update(float deltaTime) override;
		void FixedUpdate(float) override;
	    void DebugRendering() const override;
		CollisionResult RayRectCollisionCheck(const glm::vec2& rayOrigin, const glm::vec2& rayDirection, const glm::vec2& rectOrigin, const glm::vec2& rectSize);
		CollisionResult RectRectCollisionCheck(const glm::vec2& rect1Origin, const glm::vec2& rect1Size,const glm::vec2& rect1Velocity ,const glm::vec2& rect2Origin, const glm::vec2& rect2Size, float deltaTime);

	    // Getters & Setters
		bool GetIsStatic() const { return m_ColliderInfo.isStatic; }
		glm::vec3 GetPosition() const { return GetOwner()->GetLocalPosition() + glm::vec3{m_ColliderInfo.offset, 0}; }
		glm::vec2 GetSize() const { return m_ColliderInfo.size; }

	private:
	    struct CollisionInfo
	    {
			bool hit;
			float time;
			glm::vec2 normal;
	    };
		// Private Methods
		//---------------
		bool CheckCollision(const ColliderComponent* other) const;
		void ResolveCollision(const ColliderComponent* other) const;
		CollisionInfo SweptAABB(const ColliderComponent* other, const glm::vec2& velocity) const;

		// Private Members
		//---------------
		ColliderInfo m_ColliderInfo{};
		cat::MovementComponent* m_pMovementComponent{ nullptr };
    };
}
