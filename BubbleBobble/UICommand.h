#pragma once
#include "Command.h"
#include "ServiceLocator.h"
#include "UIComponent.h"
#include "UIInputSystem.h"

namespace cat
{
	class NavigationDownCommand : public dae::GameActorCommand
	{

	public:
		NavigationDownCommand(dae::GameObject* obj)
			: GameActorCommand(obj)
		{
		}


		void Execute() override
		{
			if (auto* previousComponent = dae::ServiceLocator::GetInstance().GetUIInputSystem().GetNextUIComponent(GetGameActor()->GetComponent<dae::UIComponent>()))
			{
				this->GetGameActor()->GetComponent<dae::UIComponent>()->Selected = false;
				previousComponent->Selected = true;
			}
		}
	};

	class NavigationUpCommand : public dae::GameActorCommand
	{
	public:
		NavigationUpCommand(dae::GameObject* obj)
			: GameActorCommand(obj)
		{
		}
		void Execute() override
		{
			if (auto* nextComponent = dae::ServiceLocator::GetInstance().GetUIInputSystem().GetPreviousUIComponent(GetGameActor()->GetComponent<dae::UIComponent>()))
			{
				this->GetGameActor()->GetComponent<dae::UIComponent>()->Selected = false;
				nextComponent->Selected = true;
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
			if (m_buttonState.PressedThisFrame)
			{
				auto* uiComponent = GetGameActor()->GetComponent<dae::UIComponent>();
				if (uiComponent)
				{
					uiComponent->OnButtonPressed();
				}
			}
		}
	};
}
