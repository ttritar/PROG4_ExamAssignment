#pragma once

#include "BaseComponent.h"
#include "GameObject.h"

//std


namespace dae
{
	class MovementComponent;



	// swept AABB 
    class ColliderComponent final: public dae::BaseComponent
    {
    public:
		enum class ColliderTag : uint32_t {
			None = 0,

			Player = 1 << 0,
			Enemy = 1 << 1,
			Projectile = 1 << 2,
			Level = 1 << 3,
			Tag_04 = 1 << 4,
		};

	    enum class ColliderType
	    {
		    Solid=0,
			TopOnly=1,
			Trigger=2
	    };

		struct ColliderInfo
		{
			ColliderType type = ColliderType::Solid;
			bool isStatic = false;
			glm::vec2 size;
			glm::vec2 offset = { 0,0 };

			uint32_t tag = 0;
			uint32_t collisionFilter = 0xFFFFFFFF; // everything -> just think of flags, it kinda works like that
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
		void FixedUpdate(float) override;
	    void DebugRendering() const override;
		
	    // Getters & Setters
		glm::vec3 GetPosition() const { return GetOwner()->GetLocalPosition() + glm::vec3{Info.offset, 0}; }

		
		ColliderInfo Info{};
	private:
		// Private Methods
		//---------------
		bool CanCollideWith(const ColliderComponent* other) const;
		bool CheckCollision(const ColliderComponent* other) const;
		void ResolveCollision(const ColliderComponent* other) const;
		void HandleTriggerCollision(const ColliderComponent* other);
		void HandlePhysicalCollision(const ColliderComponent* other);

		// Private Members
		//---------------
		dae::MovementComponent* m_pMovementComponent{ nullptr };

    };
}
