#include "ScoreObserverComponent.h"
#include "ScoreComponent.h"


void cat::ScoreObserverComponent::Notify(const dae::Event& event, dae::GameObject* object)
{
	if (event.id == dae::make_sdbm_hash("GainScore"))
	{
		std::string text = std::to_string(object->GetComponent<ScoreComponent>()->GetCurrentScore());
		m_pTextComponent->SetText(text);
	}
}
