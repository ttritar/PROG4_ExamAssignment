#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "TextComponent.h"
#include <memory>
#include <iostream>

namespace cat
{
	class ScoreObserverComponent : public dae::BaseComponent , public dae::Observer
	{
	public:
		ScoreObserverComponent(dae::GameObject& owner)
			:BaseComponent(owner) 
		{
			m_pTextComponent = owner.GetComponent<dae::TextComponent>();
			if (!m_pTextComponent) 
			{
				std::cerr << "ScoreUIComponent::ScoreUIComponent() > Error: No TextComponent found on GameObject\n";
			}
		};
		virtual ~ScoreObserverComponent() = default;
		ScoreObserverComponent(const ScoreObserverComponent& other) = delete;
		ScoreObserverComponent(ScoreObserverComponent&& other) = delete;
		ScoreObserverComponent& operator=(const ScoreObserverComponent& other) = delete;
		ScoreObserverComponent& operator=(ScoreObserverComponent&& other) = delete;
	private:
		virtual void Notify(const dae::Event& event, dae::GameObject* object) override;

		dae::TextComponent* m_pTextComponent = nullptr;
	};
}

