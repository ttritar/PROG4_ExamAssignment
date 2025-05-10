#include "ScoreUIComponent.h"
#include "ScoreComponent.h"


void cat::ScoreUIComponent::Notify(const dae::Event& event, dae::GameObject* object)
{
	if (event.id == dae::make_sdbm_hash("GainScore"))
	{
		std::string text = "Score: " + std::to_string(object->GetComponent<ScoreComponent>()->GetCurrentScore());
		m_pTextComponent->SetText(text);
	}
}
