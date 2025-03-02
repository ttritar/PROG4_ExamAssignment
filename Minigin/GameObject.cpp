#include <string>

#include "GameObject.h"

#include "ResourceManager.h"
#include "Renderer.h"

// Datamember functions
//------------------
void dae::GameObject::Update(float deltaTime)
{
	//UpdateWorldPosition();

	for (auto& component : m_components)
	{
		component->Update(deltaTime);
	}

	auto iterator = std::remove_if(m_components.begin(), m_components.end(),	// evrything that should be removed is put on the back of the vector
		[](const std::shared_ptr<BaseComponent>& component) { return component->pendingRemove; });
	m_components.erase(iterator, m_components.end());
}

void dae::GameObject::LateUpdate(float deltaTime)
{
	for (const auto& component : m_components)
	{
		component->LateUpdate( deltaTime);
	}
}

void dae::GameObject::FixedUpdate(float fixedStep)
{
	for (const auto& component : m_components)
	{
		component->FixedUpdate(fixedStep);
	}
}

void dae::GameObject::Render() const
{

	for (const auto& component : m_components)
	{
		component->Render();
	}
}

dae::Transform dae::GameObject::GetTransform() const
{
	return m_transform;
}


// Parent-Child functions
//------------------

void dae::GameObject::SetParent(GameObject* parent,bool keepWorldPosition)
{
	//Check if the new parent is valid (not itself or one of its children)
	if (IsChild(parent) || parent == this || m_parent == parent)
		return;

	//Update position, rotation and scale
	if (parent == nullptr)
		SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPosition)
			SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
		SetPositionDirty();
	}

	//Remove itself from the previous parent (RemoveChild ? )
	if (m_parent)	
		m_parent->m_children.erase(
							std::remove( m_parent->m_children.begin(), m_parent->m_children.end(), this ),
							m_parent->m_children.end()		);

	//Set the given parent on itself.
	m_parent = parent;

	//Add itself as a child to the given parent ( AddChild ?).
	if (m_parent)	
		m_parent->m_children.push_back(this);

};

dae::GameObject* dae::GameObject::GetParent() const 
{ 
	return m_parent;
};

size_t dae::GameObject::GetChildCount()const
{ 
	return m_children.size();
};

dae::GameObject* dae::GameObject::GetChildAt(unsigned int index)const
{ 
	return m_children[index]; 
}

bool dae::GameObject::IsChild(GameObject* object) const
{
	for (GameObject* child : m_children)
	{
		if (child == object) return true;
	}

	return false;
}


// Transform functions
//------------------
void dae::GameObject::SetPositionDirty()
{
	m_positionIsDirty = true;

	for (auto& child : m_children)
		child->SetPositionDirty();
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_localPosition = pos;
	SetPositionDirty();
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	if (m_positionIsDirty)
		UpdateWorldPosition();
	return m_worldPosition;
}

void dae::GameObject::UpdateWorldPosition()
{
	if (m_positionIsDirty)
	{
		if (m_parent == nullptr)
			m_worldPosition = m_localPosition;
		else
			m_worldPosition = m_parent->GetWorldPosition() + m_localPosition;

		m_transform.SetPosition(m_worldPosition.x, m_worldPosition.y, m_worldPosition.z);
	}
	m_positionIsDirty = false;
}


