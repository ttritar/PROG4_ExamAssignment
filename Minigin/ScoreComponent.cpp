#include "ScoreComponent.h"
#include "Observer.h"
#include "GameObject.h"

void dae::ScoreComponent::GainScore(int amount)
{
	m_currentScore += amount;

	Event e(make_sdbm_hash("GainScore"));
	GetOwner()->NotifyObservers(e);

	if (m_currentScore >= 500)
	{
		Event eWin(make_sdbm_hash("WonGame"));
		GetOwner()->NotifyObservers(eWin);
	}
}
