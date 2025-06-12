#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "TextComponent.h"

#include <memory>
#include <iostream>

namespace cat
{
	class HealthUIComponent : public dae::BaseComponent, public dae::Observer
	{
	public:
		HealthUIComponent(dae::GameObject& owner)
			:BaseComponent(owner)
		{
			m_pTextComponent = owner.GetComponent<dae::TextComponent>();
			if (!m_pTextComponent)
			{
				std::cerr << "HealthUIComponent::HealthUIComponent() > Error: No TextComponent found on GameObject\n";
			}
		};
		~HealthUIComponent() = default;
		HealthUIComponent(const HealthUIComponent& other) = delete;
		HealthUIComponent(HealthUIComponent&& other) = delete;
		HealthUIComponent& operator=(const HealthUIComponent& other) = delete;
		HealthUIComponent& operator=(HealthUIComponent&& other) = delete;
	private:
		virtual void Notify(const dae::Event& event, dae::GameObject* object) override;

		dae::TextComponent* m_pTextComponent = nullptr;
	};
}


