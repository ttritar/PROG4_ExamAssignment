#include "ColliderComponent.h"

namespace dae
{/*
	void ColliderComponent::Update(float deltaTime)
	{
	}

	void ColliderComponent::Render() const
	{
		RenderDebug();
	}

	void ColliderComponent::RenderDebug() const
	{
	}*/

	//void ColliderComponent::UpdateCollision(const std::vector<ColliderComponent*>& others)
	//{
    //    for (auto* otherCollider : others)
    //    {
    //        if (otherCollider == this) continue; // skip itself
    //
    //        if (CheckCollision(otherCollider))
    //        {
    //            bool newContact = m_Contacts.insert(otherCollider->GetOwner()).second;
    //            if (newContact && m_OnEnter) {
    //                m_OnEnter({ GetOwner(), otherCollider->GetOwner() });
    //            }
    //        }
    //        else
    //        {
    //            if (m_Contacts.erase(otherCollider->GetOwner()))
    //            {
    //                if (m_OnExit)
    //                {
    //                    m_OnExit({ GetOwner(), otherCollider->GetOwner() });
    //                }
    //            }
    //        }
    //    }
	//}

	//bool ColliderComponent::CheckCollision(const ColliderComponent* other)
	//{
    //    glm::vec2 myPos = GetWorldPosition() + m_Offset;
    //    glm::vec2 otherPos = other->GetWorldPosition() + other->m_Offset;
	//}
}
