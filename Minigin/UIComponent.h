#pragma once
#include "BaseComponent.h"

// std
#include <functional>

namespace dae
{
	class UIComponent : public dae::BaseComponent
	{
	public:
		void OnButtonPressed();

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
		std::function<void()> m_OnPressedCallBack{};
	};
}

