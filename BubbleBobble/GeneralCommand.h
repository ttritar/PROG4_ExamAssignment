#pragma once
#include "Command.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ScenePresets.h"
#include "ServiceLocator.h"


namespace cat
{
	class MuteCommand : public dae::GameActorCommand
	{
	public:
		MuteCommand(dae::GameObject* obj)
			: GameActorCommand(obj)
		{
		}


		void Execute() override
		{
			if (m_buttonState.ReleasedThisFrame)
			{
				auto& soundSystem = dae::ServiceLocator::GetInstance().GetSoundSystem();
				soundSystem.ToggleMuteAllSounds();
			}
		}
	};


	class SkipCommand : public dae::GameActorCommand
	{
	public:
		SkipCommand(dae::GameObject* obj)
			: GameActorCommand(obj)
		{
		}
		void Execute() override
		{
			if (m_buttonState.PressedThisFrame)
			{
				SwitchToNextLevel();
			}
		}

	};

}
