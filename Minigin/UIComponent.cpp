#include "UIComponent.h"

#include "ServiceLocator.h"

void dae::UIComponent::Update(float)
{
	if (m_pTextComponent)
	{
		if (Selected && (m_pTextComponent->GetColor() != m_SelectedColor))
		{
			m_pTextComponent->SetColor(m_SelectedColor);
		}
		else if (!Selected && (m_pTextComponent->GetColor() == m_SelectedColor))
		{
			m_pTextComponent->SetColor({ 1.f, 1.f, 1.f, 1.f });
		}
	}
}

void dae::UIComponent::OnButtonPressed()
{
	if (m_OnPressedCallBack && Selected)
		m_OnPressedCallBack();
}

void dae::UIComponent::OnSelected()
{
	if (m_pTextComponent)
	{
		m_pTextComponent->SetColor(m_SelectedColor);
	}
}

dae::UIComponent::UIComponent(dae::GameObject& owner, std::function<void()> onPressed)
	: BaseComponent(owner), m_OnPressedCallBack(std::move(onPressed))
{
	ServiceLocator::GetInstance().GetUIInputSystem().RegisterUIComponent(this);

	if (auto* textComponent = owner.GetComponent<TextComponent>())
	{
		m_pTextComponent = textComponent;
	}
}

dae::UIComponent::~UIComponent()
{
	ServiceLocator::GetInstance().GetUIInputSystem().UnregisterUIComponent(this);
}
