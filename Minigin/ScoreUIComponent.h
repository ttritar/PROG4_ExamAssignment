#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "TextComponent.h"
#include "SteamAchievements.h"

#include <memory>
#include <iostream>

namespace dae
{
	class ScoreUIComponent : public BaseComponent , public Observer
	{
	public:
		ScoreUIComponent(std::shared_ptr<dae::GameObject> owner)
			:BaseComponent(*owner) 
		{
			m_pTextComponent = owner->GetComponent<TextComponent>();
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
		virtual void Notify(const Event& event, GameObject* object) override;

		TextComponent* m_pTextComponent = nullptr;
	};
}

