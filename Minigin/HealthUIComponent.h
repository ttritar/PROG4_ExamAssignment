#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "TextComponent.h"

#include <memory>
#include <iostream>

namespace dae
{
	class HealthUIComponent : public BaseComponent, public Observer
	{
	public:
		HealthUIComponent(std::shared_ptr<dae::GameObject> owner)
			:BaseComponent(*owner)
		{
			m_pTextComponent = owner->GetComponent<TextComponent>();
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
		virtual void Notify(const Event& event, GameObject* object) override;

		TextComponent* m_pTextComponent = nullptr;
	};
}


