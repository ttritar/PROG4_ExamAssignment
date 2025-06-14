#pragma once
#include "Scene.h"

#include "InputManager.h"
#include "UICommand.h"
#include "UIInputSystem.h"

namespace cat
{
	inline void ResetScene()
	{
		// reset
		dae::ServiceLocator::GetInstance().GetUIInputSystem().ClearUIComponents();
		dae::ServiceLocator::GetInstance().GetSoundSystem().StopAllSounds();
		dae::ServiceLocator::GetInstance().GetCollisionSystem().ClearColliders();
		dae::InputManager::GetInstance().UnbindAllCommands();
	}

	void SwitchToNextLevel();


	void SwitchToMainMenu();

	void SwitchToLVl1_1P();
	void SwitchToLvl1_2P();
	void SwitchToLvl1_Versus();

	void SwitchToLVl2_1P();
	void SwitchToLvl2_2P();
	void SwitchToLvl2_Versus();

	void SwitchToLVl3_1P();
	void SwitchToLvl3_2P();
	void SwitchToLvl3_Versus();

	void SwitchToPassword();


#pragma region Password
	struct PasswordPreset
	{
		static void SpawnPassword(dae::Scene& scene);
	};
#pragma endregion

#pragma region MainMenu
	struct MainMenuPreset
	{
		bool isPlayerOne = true;
		void SpawnMainMenu(dae::Scene& scene) const;

		static void SetCommandsAndObservers(dae::Scene& scene);
	};
#pragma endregion



#pragma region TitleScreen
	struct TitleScreenPreset
	{
		void SpawnTitleScreen(dae::Scene& scene) const;

		void SetCommandsAndObservers(dae::Scene& scene);
	};
#pragma endregion

}
