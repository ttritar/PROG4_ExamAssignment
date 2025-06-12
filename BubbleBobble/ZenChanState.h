#pragma once
#include <MovementComponent.h>

// std
#include <memory>

namespace cat
{
	class ZenChanAIComponent;

	class ZenChanState
	{
	public:
		virtual ~ZenChanState() = default;
		virtual std::unique_ptr<ZenChanState> Update(float deltaTime) = 0;
		virtual void OnEnter(ZenChanAIComponent* ai) = 0;
		virtual void OnExit() = 0;
	};


	class ChaseState : public ZenChanState
	{
	public:
		std::unique_ptr<ZenChanState> Update(float deltaTime) override;
		void OnEnter(ZenChanAIComponent* ai) override;
		void OnExit() override;
	private:
		ZenChanAIComponent* m_pAIComponent = nullptr;
		dae::MovementComponent* m_pMovementComponent = nullptr;
	};

}
