#pragma once
#include "BaseComponent.h"

// std
#include <functional>

#include "TextComponent.h"

namespace dae
{
	class UIComponent : public dae::BaseComponent
	{
	public:
		void Update(float) override;

		void OnButtonPressed();
		void OnSelected();

		void SetSelectedColor(const glm::vec4& color) { m_SelectedColor = color; }

		// CTOR & DTOR
		//--------------
		UIComponent(dae::GameObject& owner, std::function<void()> onPressed = {});
		virtual ~UIComponent();
		UIComponent(const UIComponent& other) = delete;
		UIComponent(UIComponent&& other) = delete;
		UIComponent& operator=(const UIComponent& other) = delete;
		UIComponent& operator=(UIComponent&& other) = delete;


		// Public Members
		//----------------
		bool Selected = false;
	private:
		glm::vec4 m_SelectedColor{ 1.f, 1.f, 0.f, 1.f };
		std::function<void()> m_OnPressedCallBack{};
		TextComponent* m_pTextComponent{ nullptr };
	};
}

