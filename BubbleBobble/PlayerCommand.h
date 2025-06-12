#pragma once
#include "Command.h"
#include "../BubbleBobble/AttackComponent.h"

namespace cat
{
#pragma region Movement Commands
	// MOVEMENT COMMANDS
	class MoveCommand : public dae::GameActorCommand
	{
	protected:
		float m_DX, m_DY;

	public:
		MoveCommand(dae::GameObject* obj, float dx, float dy)
			: GameActorCommand(obj),
			m_DX(dx), m_DY(dy)
		{
		}


		void Execute() override
		{
			GetGameActor()->GetComponent<dae::MovementComponent>()->Move(m_DX, m_DY);
		}
	};

	class MoveUpCommand : public MoveCommand 
	{ 
	public:
		MoveUpCommand(dae::GameObject* obj)
			: MoveCommand(obj, 0, -1) 
		{
		}
	};

	class MoveDownCommand : public MoveCommand
	{
	public:
		MoveDownCommand(dae::GameObject* obj) 
			: MoveCommand(obj, 0, 1)
		{
		}
	};

	class MoveLeftCommand : public MoveCommand
	{
	public:
		MoveLeftCommand(dae::GameObject* obj)
			: MoveCommand(obj, -1,0)
		{
		}
	};

	class MoveRightCommand : public MoveCommand
	{
	public:
		MoveRightCommand(dae::GameObject* obj)
			: MoveCommand(obj, 1,0)
		{
		}
	};

	// JUMP COMMAND
	class JumpCommand : public dae::GameActorCommand
	{
	public:
		JumpCommand(dae::GameObject* obj)
			: GameActorCommand(obj)
		{
		}

		void Execute() override
		{
			if (m_buttonState.PressedThisFrame)
			{
				GetGameActor()->GetComponent<dae::MovementComponent>()->Jump();
			}
		}
	};
# pragma endregion

#pragma region Attack Command
	// ATTACK COMMAND
	class AttackCommand : public dae::GameActorCommand
	{
	public:
		AttackCommand(dae::GameObject* obj)
			: GameActorCommand(obj)
		{
		}
		void Execute() override
		{
			if (m_buttonState.PressedThisFrame)
			{
				GetGameActor()->GetComponent<AttackComponent>()->Attack();
			}
		}
	};
#pragma endregion

}

