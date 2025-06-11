#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "TextComponent.h"
#include <memory>
#include <iostream>

namespace cat
{
	class ScoreUIComponent : public dae::BaseComponent , public dae::Observer
	{
	public:
		ScoreUIComponent(dae::GameObject& owner)
			:BaseComponent(owner) 
		{
			m_pTextComponent = owner.GetComponent<TextComponent>();
			if (!m_pTextComponent) 
			{
				std::cerr << "ScoreUIComponent::ScoreUIComponent() > Error: No TextComponent found on GameObject\n";
			}
		};
		~ScoreUIComponent() = default;
		ScoreUIComponent(const ScoreUIComponent& other) = delete;
		ScoreUIComponent(ScoreUIComponent&& other) = delete;
		ScoreUIComponent& operator=(const ScoreUIComponent& other) = delete;
		ScoreUIComponent& operator=(ScoreUIComponent&& other) = delete;
	private:
		virtual void Notify(const dae::Event& event, dae::GameObject* object) override;

		TextComponent* m_pTextComponent = nullptr;
	};
}

