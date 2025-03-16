#include "HealthUIComponent.h"
#include "HealthComponent.h"

void dae::HealthUIComponent::Notify(const Event& event, GameObject* object)
{
	if (event.id == make_sdbm_hash("PlayerDied"))
	{
		std::string text = "# lives: " + std::to_string(object->GetComponent<HealthComponent>()->GetCurrentHealth());
		m_pTextComponent->SetText(text);
	}
}
