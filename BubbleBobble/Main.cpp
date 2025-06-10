
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "MixerSoundSystem.h"
#include "ServiceLocator.h"

#include <SDL.h>

#include "ColliderComponent.h"
#include "CollisionSystem.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "HealthUIComponent.h"

#include "InputManager.h"
#include "MovementComponent.h"
#include "Level.h"
#include "MaitaAIComponent.h"
#include "ScoreUIComponent.h"


void load()
{
	auto& scene1 = dae::SceneManager::GetInstance().CreateScene("Level1");
	auto level = cat::Level(scene1,1, "../Data/Levels/Level1.tmj");

	//auto& scene2 = dae::SceneManager::GetInstance().CreateScene("Level2");
	//auto level2 = cat::Level(scene2, 2, "../Data/Levels/Level2.tmj");

	// TUT TEXT
	//----------

	//auto fontUI = dae::ResourceManager::GetInstance().LoadFont("font.ttf",20);


	//// BUBBLUN
	////----------------
	// auto bubblunHealthObserver = std::make_shared<dae::GameObject>();
	// auto textHealthBubblun = std::make_shared<cat::TextComponent>(bubblunHealthObserver, "3", fontUI);
	// bubblunHealthObserver->AddComponent(textHealthBubblun);
	// auto uicHealthBubblun = std::make_shared<cat::HealthUIComponent>(bubblunHealthObserver);
	// bubblunHealthObserver->AddComponent(uicHealthBubblun);
	// bubblunHealthObserver->SetLocalPosition({ 50,600,0 });
	// scene1.Add(bubblunHealthObserver);
	// 
	// auto bubblunScoreObserver = std::make_shared<dae::GameObject>();
	// auto textScoreBubblun = std::make_shared<cat::TextComponent>(bubblunScoreObserver, "90700", fontUI);
	// bubblunScoreObserver->AddComponent(textScoreBubblun);
	// auto uicScoreBubblun = std::make_shared<cat::ScoreUIComponent>(bubblunScoreObserver);
	// bubblunScoreObserver->AddComponent(uicScoreBubblun);
	// bubblunScoreObserver->SetLocalPosition({ 100,20,0 });
	// scene1.Add(bubblunScoreObserver);


	//// bubblun->AddObserver(uicHealthBubblun.get());
	//// bubblun->AddObserver(uicScoreBubblun.get());

	////auto bubblunScore = std::make_shared<cat::ScoreComponent>(bubblun);
	////bubblun->AddComponent(bubblunScore);

	//// MAITA
	////----------------
	//auto maita = std::make_shared<dae::GameObject>();
	//maita->SetLocalPosition({ 50, 50,0 });

	//auto maitaTexture = std::make_shared<cat::TextureComponent>(maita, "Enemies/Maita.png");
	//maita->AddComponent(maitaTexture);

	//auto maitaMove = std::make_shared<cat::MovementComponent>(maita, 90.f);
	//maitaMove->SetUsesGravity(false);
	//maita->AddComponent(maitaMove);

	//auto maitaAI = std::make_shared<cat::MaitaAIComponent>(maita);
	////maitaAI->AddPlayer(bubblun);
	//maita->AddComponent(maitaAI);

	//cat::ColliderComponent::ColliderInfo maitaColliderInfo{
	//	cat::ColliderComponent::ColliderType::Trigger,false, {48.f,48.f}
	//};
	//auto maitaColl = std::make_shared<cat::ColliderComponent>(maita,maitaColliderInfo);
	//cat::CollisionSystem::GetInstance().AddCollider(maitaColl.get());
	//maita->AddComponent(maitaAI);

	//scene1.Add(maita);

}



int main(int, char* [])
{
	{

		auto& serviceLocator = dae::ServiceLocator::GetInstance();
		serviceLocator.RegisterSoundSystem(std::make_unique<dae::MixerSoundSystem>());

		dae::Minigin engine("../Data/");
		engine.Run(load);
	}

	VLDReportLeaks();

	return 0;
}

