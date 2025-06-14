#pragma once
#include "Observer.h"

#include "ColliderComponent.h"


namespace cat
{
	class EnemyCollisionObserverComponent final : public dae::BaseComponent, public dae::Observer
	{
	public:
		void Notify(const dae::Event& event, dae::GameObject* object) override;

		// CTOR & DTOR
		//--------------
		EnemyCollisionObserverComponent(dae::GameObject& owner)
			: BaseComponent(owner)
		{
			// No initialization needed
		};
		virtual ~EnemyCollisionObserverComponent() = default;
		EnemyCollisionObserverComponent(const EnemyCollisionObserverComponent& other) = delete;
		EnemyCollisionObserverComponent(EnemyCollisionObserverComponent&& other) = delete;
		EnemyCollisionObserverComponent& operator=(const EnemyCollisionObserverComponent& other) = delete;
		EnemyCollisionObserverComponent& operator=(EnemyCollisionObserverComponent&& other) = delete;

	};

	class PlayerCollisionObserverComponent final : public dae::BaseComponent, public dae::Observer
	{
	public:
		void Notify(const dae::Event& event, dae::GameObject* object) override;

		// CTOR & DTOR
		//--------------
		PlayerCollisionObserverComponent(dae::GameObject& owner)
			: BaseComponent(owner)
		{
			// No initialization needed
		};
		virtual ~PlayerCollisionObserverComponent() = default;
		PlayerCollisionObserverComponent(const PlayerCollisionObserverComponent& other) = delete;
		PlayerCollisionObserverComponent(PlayerCollisionObserverComponent&& other) = delete;
		PlayerCollisionObserverComponent& operator=(const PlayerCollisionObserverComponent& other) = delete;
		PlayerCollisionObserverComponent& operator=(PlayerCollisionObserverComponent&& other) = delete;

	};
}
