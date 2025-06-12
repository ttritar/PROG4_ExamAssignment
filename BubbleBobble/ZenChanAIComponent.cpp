#include "ZenChanAIComponent.h"

void cat::ZenChanAIComponent::Update(float deltaTime)
{
	// STATE
	//-----------------
	std::unique_ptr<ZenChanState> newState = nullptr;
	if (m_CurrentState)
	{
		newState = m_CurrentState->Update(deltaTime);
	}
	if (newState)
	{
		ChangeState(std::move(newState));
	}

}

void cat::ZenChanAIComponent::ChangeState(std::unique_ptr<ZenChanState> newState)
{
	if (m_CurrentState) m_CurrentState->OnExit();
	m_CurrentState = std::move(newState);
	if (m_CurrentState) m_CurrentState->OnEnter(this);
}
