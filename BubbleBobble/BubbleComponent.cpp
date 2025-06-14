
#include "BubbleComponent.h"

#include "Presets.h"

cat::BubbleComponent::BubbleComponent(dae::GameObject& owner): BaseComponent(owner)
{
	m_CurrentState = std::make_unique<ShootingState>();
	m_CurrentState->OnEnter(this);
}

cat::BubbleComponent::BubbleComponent(dae::GameObject& owner, TrappedEnemyType enemy): BaseComponent(owner)
{
	m_CurrentState = std::make_unique<RisingState>();
	m_CurrentState->OnEnter(this);

	TrappedEnemy = enemy;
	if (enemy == TrappedEnemyType::ZenChan)
	{
		owner.GetComponent<AnimationComponent>()->FrameData.row += 2;
	}
	else if (enemy == TrappedEnemyType::Maita)
	{
		owner.GetComponent<AnimationComponent>()->FrameData.row += 4;
	}
	HasTrapped = true;
}

void cat::BubbleComponent::Update(float deltaTime)
{
	m_Lifetime += deltaTime;
	if (m_Lifetime > m_MaxLifetime)
	{
		if (HasTrapped)
		{
			if (TrappedEnemy == TrappedEnemyType::ZenChan)
			{
				auto& scene = dae::SceneManager::GetInstance().GetActiveScene();
				ZenChanPreset::SpawnZenChan(scene, GetOwner()->GetWorldPosition());
			}
		}
		GetOwner()->m_pendingRemoval = true;
	}

	// STATE
	//-----------------
	std::unique_ptr<BubbleState> newState = nullptr;
	if (m_CurrentState)
	{
		newState = m_CurrentState->Update(deltaTime);
	}
	if (newState)
	{
		ChangeState(std::move(newState));
	}
}

void cat::BubbleComponent::ChangeState(std::unique_ptr<BubbleState> newState)
{
	if (m_CurrentState) m_CurrentState->OnExit();
	m_CurrentState = std::move(newState);
	if (m_CurrentState) m_CurrentState->OnEnter(this);
}
