#include "ScoreComponent.h"
#include "Observer.h"
#include "GameObject.h"

void cat::ScoreComponent::GainScore(int amount)
{
	m_currentScore += amount;

	dae::Event e(dae::make_sdbm_hash("GainScore"));
	GetOwner()->NotifyObservers(e);

	if (m_currentScore >= 500)
	{
		dae::Event eWin(dae::make_sdbm_hash("WonGame"));
		GetOwner()->NotifyObservers(eWin);
	}
}
