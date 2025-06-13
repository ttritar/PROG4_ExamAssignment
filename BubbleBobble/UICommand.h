#pragma once
#include "Command.h"
#include "ServiceLocator.h"
#include "UIComponent.h"
#include "UIInputSystem.h"

namespace cat
{
	class NavigationNextCommand : public dae::GameActorCommand
	{

	public:
		NavigationNextCommand(dae::GameObject* obj)
			: GameActorCommand(obj)
		{
		}


		void Execute() override
		{
			if (m_buttonState.ReleasedThisFrame)
			{
				auto& uiSystem = dae::ServiceLocator::GetInstance().GetUIInputSystem();
				auto* current = uiSystem.GetSelectedUIComponent();
				if (auto* next = uiSystem.GetNextUIComponent(current))
				{
					uiSystem.SetSelectedUIComponent(next);
					next->OnSelected();
				}
			}
		}
	};

	class NavigationPreviousCommand : public dae::GameActorCommand
	{
	public:
		NavigationPreviousCommand(dae::GameObject* obj)
			: GameActorCommand(obj)
		{
		}
		void Execute() override
		{
			if (m_buttonState.ReleasedThisFrame)
			{
				auto& uiSystem = dae::ServiceLocator::GetInstance().GetUIInputSystem();
				auto* current = uiSystem.GetSelectedUIComponent();
				if (auto* previous = uiSystem.GetPreviousUIComponent(current))
				{
					uiSystem.SetSelectedUIComponent(previous);
					previous->OnSelected();
				}
			}
		}
	};


	class PressButtonCommand : public dae::GameActorCommand
	{
	public:
		PressButtonCommand(dae::GameObject* obj)
			: GameActorCommand(obj)
		{
		}
		void Execute() override
		{
			if (m_buttonState.ReleasedThisFrame)
			{
				auto* selected = dae::ServiceLocator::GetInstance().GetUIInputSystem().GetSelectedUIComponent();
				if (selected)
				{
					selected->OnButtonPressed();
				}
			}
		}
	};

	class CustomUICommand : public dae::GameActorCommand
	{
	protected:
		std::function<void()> m_customCallback;

	public:
		CustomUICommand(dae::GameObject* obj, std::function<void()> customCallback)
			: GameActorCommand(obj), m_customCallback(std::move(customCallback))
		{
		}
		void Execute() override
		{
			if (m_buttonState.ReleasedThisFrame)
			{
				m_customCallback();
			}
		}
	};
}
