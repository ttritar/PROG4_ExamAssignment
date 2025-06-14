
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif
#include "Minigin.h"
#include "MixerSoundSystem.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "ScenePresets.h"


void load()
{

	// LEVELS
	//----------

	//----- main menu -----
	{
		auto& sceneTitleScreen = dae::SceneManager::GetInstance().CreateScene("TitleScreen");
		cat::TitleScreenPreset titleScreenPreset{};
		titleScreenPreset.SpawnTitleScreen(sceneTitleScreen);
		titleScreenPreset.SetCommandsAndObservers(sceneTitleScreen);
	}

	// SET ACTIVE
	dae::SceneManager::GetInstance().SetActiveScene("TitleScreen");

}



int main(int, char* [])
{
	{
		auto& serviceLocator = dae::ServiceLocator::GetInstance();
		serviceLocator.RegisterSoundSystem(std::make_unique<dae::MixerSoundSystem>());
		serviceLocator.RegisterCollisionSystem(std::make_unique<dae::CollisionSystem>());
		serviceLocator.RegisterPlayerSystem(std::make_unique<dae::PlayerSystem>());
		serviceLocator.RegisterUIInputSystem(std::make_unique<dae::UIInputSystem>());

		dae::Minigin engine("../Data/");
		engine.Run(load);
	}

	return 0;
}

