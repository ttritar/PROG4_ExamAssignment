#include "UIInputSystem.h" 

#include "ServiceLocator.h"

void dae::UIInputSystem::RegisterUIComponent(dae::UIComponent* uiComponent)
{
	if (uiComponent == nullptr) return;

	auto it = std::find(m_UIComponents.begin(), m_UIComponents.end(), uiComponent);
	if (it == m_UIComponents.end())
	{
		m_UIComponents.push_back(uiComponent);
	}
}

void dae::UIInputSystem::UnregisterUIComponent(dae::UIComponent* uiComponent)
{
	auto it = std::remove(m_UIComponents.begin(), m_UIComponents.end(), uiComponent);
	if (it != m_UIComponents.end())
	{
		m_UIComponents.erase(it, m_UIComponents.end());
	}
}

void dae::UIInputSystem::ClearUIComponents()
{
	m_UIComponents.clear();
}

std::vector<dae::UIComponent*> dae::UIInputSystem::GetUIComponents()
{
	return m_UIComponents;
}

dae::UIComponent* dae::UIInputSystem::GetUIComponent(int idx) const
{
	if (idx < 0 || idx >= static_cast<int>(m_UIComponents.size()))
	{
		return nullptr; 
	}
	return m_UIComponents[idx];
}

dae::UIComponent* dae::UIInputSystem::GetNextUIComponent(UIComponent* uiComponent) const
{
	if (uiComponent == nullptr || m_UIComponents.empty()) return nullptr;

	auto it = std::find(m_UIComponents.begin(), m_UIComponents.end(), uiComponent);
	if (it != m_UIComponents.end())
	{
		if (it != m_UIComponents.end())
		{
			++it;
			if (it == m_UIComponents.end())
				it = m_UIComponents.begin();
			return *it;
		}
	}
	return nullptr;
}

dae::UIComponent* dae::UIInputSystem::GetPreviousUIComponent(UIComponent* uiComponent) const
{
	if (uiComponent == nullptr || m_UIComponents.empty()) return nullptr;

	auto it = std::find(m_UIComponents.begin(), m_UIComponents.end(), uiComponent);
	if (it != m_UIComponents.end())
	{
		if (it == m_UIComponents.begin())
		{
			it = m_UIComponents.end() - 1;
		}
		else
		{
			--it;
		}
		return *it;
	}
	return nullptr;
}
