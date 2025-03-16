#include "ScoreUIComponent.h"
#include "ScoreComponent.h"


void dae::ScoreUIComponent::Notify(const Event& event, GameObject* object)
{
	if (event.id == make_sdbm_hash("GainScore"))
	{
		std::string text = "Score: " + std::to_string(object->GetComponent<ScoreComponent>()->GetCurrentScore());
		m_pTextComponent->SetText(text);
	}
	
	else if (event.id == make_sdbm_hash("WonGame"))
	{
		UnlockAchievement("ACH_WIN_ONE_GAME");
	}
}
