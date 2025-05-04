#pragma once

#include "BaseComponent.h"

//std
#include <memory>
#include <vector>

//namespace dae
//{
//
//	enum class Shape2D
//	{
//		AABB,
//		Circle
//	};
//
//	struct ColliderInfo
//	{
//		Shape2D shape;
//		glm::vec2 offset = {0,0};
//		glm::vec2 halfSize;
//	};
//
//    class ColliderComponent final: dae::BaseComponent
//    {
//    public:
//
//		// Methods
//		//---------------
//		void Update(float deltaTime) override;
//		void Render() const override;
//		void SetDebugRendering(bool value) { m_IsDebugRendering = value; }
//
//		void UpdateCollision(const std::vector<ColliderComponent*>& others);
//
//		// CTOR & DTOR
//		//---------------
//		//ColliderComponent::ColliderComponent(const std::shared_ptr<dae::GameObject>& owner, ColliderInfo colliderInfo)
//		//	:BaseComponent(*owner), m_ColliderInfo(colliderInfo)
//		//{
//		//}
//		//virtual ~ColliderComponent() = default;
//		//ColliderComponent(const ColliderComponent& other) = delete;
//		//ColliderComponent(ColliderComponent&& other) = delete;
//		//ColliderComponent& operator=(const ColliderComponent& other) = delete;
//		//ColliderComponent& operator=(ColliderComponent&& other) = delete;
//
//	private:
//		// Private Methods
//		//---------------
//		void RenderDebug()const;
//		bool CheckCollision(const ColliderComponent* other);
//
//		bool AABBvsAABB();
//		bool CirclevsCircle();
//		bool AABBvsCircle();
//		
//
//
//		// Private Members
//		//---------------
//		bool m_IsDebugRendering{};
//
//		ColliderInfo m_ColliderInfo{};
//    };
//}
