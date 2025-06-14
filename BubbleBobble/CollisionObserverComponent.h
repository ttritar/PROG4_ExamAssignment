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

	class ItemCollisionObserverComponent final : public dae::BaseComponent, public dae::Observer
	{
	public:
		void Notify(const dae::Event& event, dae::GameObject* object) override;

		// CTOR & DTOR
		//--------------
		ItemCollisionObserverComponent(dae::GameObject& owner)
			: BaseComponent(owner)
		{
			// No initialization needed
		};
		virtual ~ItemCollisionObserverComponent() = default;
		ItemCollisionObserverComponent(const ItemCollisionObserverComponent& other) = delete;
		ItemCollisionObserverComponent(ItemCollisionObserverComponent&& other) = delete;
		ItemCollisionObserverComponent& operator=(const ItemCollisionObserverComponent& other) = delete;
		ItemCollisionObserverComponent& operator=(ItemCollisionObserverComponent&& other) = delete;

	};
}
