#pragma once
#include <iostream>

#include "Observer.h"
#include "TextComponent.h"

namespace cat
{
	class HealthObserverComponent : public dae::BaseComponent, public dae::Observer
	{
	public:
		HealthObserverComponent(dae::GameObject& owner)
			:BaseComponent(owner)
		{
			m_pTextComponent = owner.GetComponent<dae::TextComponent>();
			if (!m_pTextComponent)
			{
				std::cerr << "ScoreUIComponent::ScoreUIComponent() > Error: No TextComponent found on GameObject\n";
			}
		};
		virtual ~HealthObserverComponent() = default;
		HealthObserverComponent(const HealthObserverComponent& other) = delete;
		HealthObserverComponent(HealthObserverComponent&& other) = delete;
		HealthObserverComponent& operator=(const HealthObserverComponent& other) = delete;
		HealthObserverComponent& operator=(HealthObserverComponent&& other) = delete;
	private:
		virtual void Notify(const dae::Event& event, dae::GameObject* object) override;

		dae::TextComponent* m_pTextComponent = nullptr;
	};
}
