#pragma once
#include <memory>
#include <random>

#include "Scene.h"

#include "AnimationComponent.h"
#include "InputManager.h"
#include "MovementComponent.h"
#include "TextComponent.h"
#include "UICommand.h"
#include "UIComponent.h"
#include "UIInputSystem.h"
#include "WindowInfo.h"

namespace cat
{
	inline void ResetScene()
	{
		// reset
		dae::ServiceLocator::GetInstance().GetUIInputSystem().ClearUIComponents();
		dae::InputManager::GetInstance().UnbindAllBtnCommands();
	}


	static void SwitchToMainMenu();

	static void SwitchToLVl1_1P();
	static void SwitchToLvl1_2P();
	static void SwitchToLvl1_Versus();

	static void SwitchToLVl2_1P();
	static void SwitchToLvl2_2P();
	static void SwitchToLvl2_Versus();

	static void SwitchToPassword();


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
