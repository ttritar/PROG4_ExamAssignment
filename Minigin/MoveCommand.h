#pragma once
#include "Command.h"
#include "MovementComponent.h"

namespace dae
{
	class MoveCommand : public GameActorCommand
	{
	protected:
		float m_DX, m_DY;

	public:
		MoveCommand(GameObject* obj, float dx, float dy)
			: GameActorCommand(obj),
			m_DX(dx), m_DY(dy)
		{
		}


		void Execute() override
		{
			GetGameActor()->GetComponent<MovementComponent>()->Move(m_DX, m_DY);
		}
	};

	class MoveUpCommand : public MoveCommand 
	{ 
	public:
		MoveUpCommand(GameObject* obj)
			: MoveCommand(obj, 0, -1) 
		{
		}
	};

	class MoveDownCommand : public MoveCommand
	{
	public:
		MoveDownCommand(GameObject* obj) 
			: MoveCommand(obj, 0, 1)
		{
		}
	};

	class MoveLeftCommand : public MoveCommand
	{
	public:
		MoveLeftCommand(GameObject* obj)
			: MoveCommand(obj, -1,0)
		{
		}
	};

	class MoveRightCommand : public MoveCommand
	{
	public:
		MoveRightCommand(GameObject* obj)
			: MoveCommand(obj, 1,0)
		{
		}
	};
}

