#include "UIComponent.h"

#include "ServiceLocator.h"

void dae::UIComponent::OnButtonPressed()
{
	if (m_OnPressedCallBack && Selected)
		m_OnPressedCallBack();
}

dae::UIComponent::UIComponent(dae::GameObject& owner, std::function<void()> onPressed)
	: BaseComponent(owner), m_OnPressedCallBack(std::move(onPressed))
{
	ServiceLocator::GetInstance().GetUIInputSystem().RegisterUIComponent(this);
}

dae::UIComponent::~UIComponent()
{
	ServiceLocator::GetInstance().GetUIInputSystem().UnregisterUIComponent(this);
}
