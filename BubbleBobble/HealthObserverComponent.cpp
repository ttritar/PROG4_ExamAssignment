#include "HealthObserverComponent.h"

#include "HealthComponent.h"
#include "HighScore.h"
#include "ScenePresets.h"
#include "ScoreComponent.h"
#include "ServiceLocator.h"

void cat::HealthObserverComponent::Notify(const dae::Event& event, dae::GameObject* object)
{
	if (event.id == dae::make_sdbm_hash("LoseHealth"))
	{
		std::string text = std::to_string(object->GetComponent<HealthComponent>()->GetCurrentHealth());
		m_pTextComponent->SetText(text);

		// sound
		auto& ss = dae::ServiceLocator::GetInstance().GetSoundSystem();
		const dae::sound_id soundId = static_cast<dae::sound_id>(dae::make_sdbm_hash("PlayerHurt"));
		ss.LoadSound(soundId, "Players/Death.wav");
		ss.Play(soundId, 100);
	}

	if (event.id == dae::make_sdbm_hash("LoseGame"))
	{
		SwitchToPassword();
	}
}
