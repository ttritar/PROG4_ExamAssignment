#pragma once
#include "GameObject.h"

namespace dae
{
	struct InputType
	{
		bool Controller = false;
		bool Keyboard = false;
	};

	struct ButtonState
	{
		bool PressedThisFrame = false;
		bool ReleasedThisFrame = false;
		bool Down = false;
	};

	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};



	class GameActorCommand : public Command
	{
		GameObject* m_actor;
	protected:
		GameObject* GetGameActor() const { return m_actor; }
	public:
		GameActorCommand(GameObject* obj) { m_actor = obj; };
		virtual ~GameActorCommand() {};

		ButtonState m_buttonState{};
		InputType m_inputType{};
	};

}