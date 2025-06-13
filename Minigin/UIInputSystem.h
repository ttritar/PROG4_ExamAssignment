#pragma once

#pragma once
#include <unordered_map>
#include <xstring>
#include "UIComponent.h"

namespace dae
{
	class UIInputSystem
	{
	public:
		void RegisterUIComponent(dae::UIComponent* uiComponent);
		void UnregisterUIComponent(dae::UIComponent* uiComponent);
		void ClearUIComponents();
		std::vector <dae::UIComponent*> GetUIComponents();
		dae::UIComponent* GetUIComponent(int idx) const;
		UIComponent* GetNextUIComponent(UIComponent* uiComponent) const;
		UIComponent* GetPreviousUIComponent(UIComponent* uiComponent) const;

		UIComponent* GetSelectedUIComponent() const { return m_SelectedUIComponent; }
		void SetSelectedUIComponent(UIComponent* uiComponent)
		{
			if (m_SelectedUIComponent)
				m_SelectedUIComponent->Selected = false;

			m_SelectedUIComponent = uiComponent;

			if (m_SelectedUIComponent)
				m_SelectedUIComponent->Selected = true;
		}
	private:
		std::vector<UIComponent*> m_UIComponents;
		UIComponent* m_SelectedUIComponent = nullptr;
	};
}
