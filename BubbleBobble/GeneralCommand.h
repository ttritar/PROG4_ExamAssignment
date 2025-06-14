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
				const std::string& name = dae::SceneManager::GetInstance().GetActiveScene().GetName();

				//----- LEVEL 1 -----------------
				if (name == "Level1_SinglePlayer")
				{
					cat::SwitchToLVl2_1P();
				}
				else if (name == "Level1_Multiplayer")
				{
					cat::SwitchToLvl2_2P();
				}
				else if (name == "Level1_Versus")
				{
					cat::SwitchToLvl2_Versus();
				}

				//----- LEVEL 2 -----------------
				else if (name == "Level2_SinglePlayer" ||
					name == "Level2_Multiplayer" ||
					name == "Level2_Versus")
				{
					cat::SwitchToMainMenu();
				}
			}
		}

	};

}
