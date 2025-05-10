#include "HealthUIComponent.h"
#include "HealthComponent.h"

void cat::HealthUIComponent::Notify(const dae::Event& event, dae::GameObject* object)
{
	if (event.id == dae::make_sdbm_hash("PlayerDied"))
	{
		std::string text = "# lives: " + std::to_string(object->GetComponent<HealthComponent>()->GetCurrentHealth());
		m_pTextComponent->SetText(text);
	}
}


