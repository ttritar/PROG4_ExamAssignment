
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif
#include "Level.h"
#include "Minigin.h"
#include "MixerSoundSystem.h"
#include "SceneManager.h"
#include "ServiceLocator.h"


void load()
{
	auto& scene1 = dae::SceneManager::GetInstance().CreateScene("Level1");
	auto level = cat::Level(scene1,1, "../Data/Levels/Level1.tmj");

	//auto& scene2 = dae::SceneManager::GetInstance().CreateScene("Level2");
	//auto level2 = cat::Level(scene2, 2, "../Data/Levels/Level2.tmj");

	// TUT TEXT
	//----------

}



int main(int, char* [])
{
	{

		auto& serviceLocator = dae::ServiceLocator::GetInstance();
		serviceLocator.RegisterSoundSystem(std::make_unique<dae::MixerSoundSystem>());

		dae::Minigin engine("../Data/");
		engine.Run(load);
	}

	return 0;
}

