#include "ScoreComponent.h"
#include "Observer.h"
#include "GameObject.h"

cat::ScoreComponent::ScoreComponent(dae::GameObject& owner)
	:BaseComponent(owner)
{
}

void cat::ScoreComponent::GainScore(int amount)
{
	m_currentScore += amount;

	dae::Event e(dae::make_sdbm_hash("GainScore"));
	GetOwner()->NotifyObservers(e);
}
