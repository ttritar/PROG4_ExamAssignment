
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

#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "RotationComponent.h"

#include "InputManager.h"
#include "Command.h"
#include "MoveCommand.h"
#include "MovementComponent.h"
#include "HealthComponent.h"
#include "UICommand.h"
#include "HealthUIComponent.h"
#include "ScoreUIComponent.h"


void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	// add textures
	auto go = std::make_shared<dae::GameObject>();
	auto texture1 = std::make_shared<dae::TextureComponent>(go, "background.tga");
	go->AddComponent(texture1);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	auto texture2 = std::make_shared<dae::TextureComponent>(go, "logo.tga");
	go->SetLocalPosition(glm::vec3{ 216, 180,0 });
	go->AddComponent(texture2);
	scene.Add(go);

	// add text
	go = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto tc = std::make_shared<dae::TextComponent>(go, "Programming 4 Assignment", font);
	go->SetLocalPosition(glm::vec3{ 80, 20,0 });
	go->AddComponent(tc);
	scene.Add(go);


	// FPS COMPONENT
	//-------------
	go = std::make_shared<dae::GameObject>();
	auto fpstc = std::make_shared<dae::TextComponent>(go, "FPS", font);
	go->AddComponent(fpstc);
	auto fps = std::make_shared<dae::FPSComponent>(go);
	go->AddComponent(fps);
	go->SetLocalPosition(glm::vec3{ 80, 60,0 });
	scene.Add(go);




	auto& inputManager = dae::InputManager::GetInstance();

	auto fontUI = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);

	auto tutTextBubblun = std::make_shared<dae::GameObject>();
	tutTextBubblun->SetLocalPosition({ 20, 130, 0 });
	auto text0 = std::make_shared<dae::TextComponent>(tutTextBubblun, "Use WASD to move Bubblun, C to inflict damage, Z and X to pick up pellets.", fontUI);
	tutTextBubblun->AddComponent(text0);
	scene.Add(tutTextBubblun);

	auto tutTextBobblun = std::make_shared<dae::GameObject>();
	tutTextBobblun->SetLocalPosition({ 20, 150, 0 });
	auto text1 = std::make_shared<dae::TextComponent>(tutTextBobblun, "Use the D-Pad to move Bobblun, X to inflict damage, A and B to pick up pellets.", fontUI);
	tutTextBobblun->AddComponent(text1);
	scene.Add(tutTextBobblun);



	// BUBBLUN
	//----------------
	auto bubblunHealthObserver = std::make_shared<dae::GameObject>();
	auto textHealthBubblun = std::make_shared<dae::TextComponent>(bubblunHealthObserver, "# lives: 3", fontUI);
	bubblunHealthObserver->AddComponent(textHealthBubblun);
	auto uicHealthBubblun = std::make_shared<dae::HealthUIComponent>(bubblunHealthObserver);
	bubblunHealthObserver->AddComponent(uicHealthBubblun);
	bubblunHealthObserver->SetLocalPosition({ 20,200,0 });
	scene.Add(bubblunHealthObserver);

	auto bubblunScoreObserver = std::make_shared<dae::GameObject>();
	auto textScoreBubblun = std::make_shared<dae::TextComponent>(bubblunScoreObserver, "Score: 0", fontUI);
	bubblunScoreObserver->AddComponent(textScoreBubblun);
	auto uicScoreBubblun = std::make_shared<dae::ScoreUIComponent>(bubblunScoreObserver);
	bubblunScoreObserver->AddComponent(uicScoreBubblun);
	bubblunScoreObserver->SetLocalPosition({ 20,220,0 });
	scene.Add(bubblunScoreObserver);



	auto bubblun = std::make_shared<dae::GameObject>();

	bubblun->AddObserver(uicHealthBubblun.get());
	bubblun->AddObserver(uicScoreBubblun.get());

	auto bubblunTexture = std::make_shared<dae::TextureComponent>(bubblun, "Bubblun.png");
	bubblun->AddComponent(bubblunTexture);
	bubblun->SetLocalPosition({ 100,100,0 });

	auto bubblunMove = std::make_shared<dae::MovementComponent>(bubblun, 50.f);
	bubblun->AddComponent(bubblunMove);

	inputManager.BindKeyCommand(SDLK_w, std::make_unique<dae::MoveUpCommand>(dae::MoveUpCommand(bubblun.get())));
	inputManager.BindKeyCommand(SDLK_s, std::make_unique<dae::MoveDownCommand>(dae::MoveDownCommand(bubblun.get())));
	inputManager.BindKeyCommand(SDLK_a, std::make_unique<dae::MoveLeftCommand>(dae::MoveLeftCommand(bubblun.get())));
	inputManager.BindKeyCommand(SDLK_d, std::make_unique<dae::MoveRightCommand>(dae::MoveRightCommand(bubblun.get())));

	auto bubblunHealth = std::make_shared<dae::HealthComponent>(bubblun, 3);
	bubblun->AddComponent(bubblunHealth);

	auto bubblunScore = std::make_shared<dae::ScoreComponent>(bubblun);
	bubblun->AddComponent(bubblunScore);

	inputManager.BindKeyCommand(SDLK_c, std::make_unique<dae::DamageCommand>(dae::DamageCommand(bubblun.get(), 1)));
	inputManager.BindKeyCommand(SDLK_z, std::make_unique<dae::ScoreCommand>(dae::ScoreCommand(bubblun.get(), 10)));
	inputManager.BindKeyCommand(SDLK_x, std::make_unique<dae::ScoreCommand>(dae::ScoreCommand(bubblun.get(), 100)));



	// BOBBLUN
	//----------------
	auto bobblunHealthObserver = std::make_shared<dae::GameObject>();
	auto textHealthBobblun = std::make_shared<dae::TextComponent>(bobblunHealthObserver, "# lives: 3", fontUI);
	bobblunHealthObserver->AddComponent(textHealthBobblun);
	auto uicHealthBobblun = std::make_shared<dae::HealthUIComponent>(bobblunHealthObserver);
	bobblunHealthObserver->AddComponent(uicHealthBobblun);
	bobblunHealthObserver->SetLocalPosition({ 20,250,0 });
	scene.Add(bobblunHealthObserver);

	auto bobblunScoreObserver = std::make_shared<dae::GameObject>();
	auto textScoreBobblun = std::make_shared<dae::TextComponent>(bobblunScoreObserver, "Score: 0", fontUI);
	bobblunScoreObserver->AddComponent(textScoreBobblun);
	auto uicScoreBobblun = std::make_shared<dae::ScoreUIComponent>(bobblunScoreObserver);
	bobblunScoreObserver->AddComponent(uicScoreBobblun);
	bobblunScoreObserver->SetLocalPosition({ 20,270,0 });
	scene.Add(bobblunScoreObserver);



	auto bobblun = std::make_shared<dae::GameObject>();

	bobblun->AddObserver(uicHealthBobblun.get());
	bobblun->AddObserver(uicScoreBobblun.get());

	auto bobblunTexture = std::make_shared<dae::TextureComponent>(bobblun, "Bobblun.png");
	bobblun->AddComponent(bobblunTexture);
	bobblun->SetLocalPosition({ 20,20,0 });

	auto bobblunMove = std::make_shared<dae::MovementComponent>(bobblun, 100.f);
	bobblun->AddComponent(bobblunMove);

	inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_DPAD_UP, std::make_unique<dae::MoveUpCommand>(dae::MoveUpCommand(bobblun.get())));
	inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_DPAD_DOWN, std::make_unique<dae::MoveDownCommand>(dae::MoveDownCommand(bobblun.get())));
	inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_DPAD_LEFT, std::make_unique<dae::MoveLeftCommand>(dae::MoveLeftCommand(bobblun.get())));
	inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_DPAD_RIGHT, std::make_unique<dae::MoveRightCommand>(dae::MoveRightCommand(bobblun.get())));

	auto bobblunHealth = std::make_shared<dae::HealthComponent>(bobblun, 3);
	bobblun->AddComponent(bobblunHealth);

	auto bobblunScore = std::make_shared<dae::ScoreComponent>(bobblun);
	bobblun->AddComponent(bobblunScore);

	inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_X, std::make_unique<dae::DamageCommand>(dae::DamageCommand(bobblun.get(), 1)));
	inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_A, std::make_unique<dae::ScoreCommand>(dae::ScoreCommand(bobblun.get(), 10)));
	inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_B, std::make_unique<dae::ScoreCommand>(dae::ScoreCommand(bobblun.get(), 100)));

	scene.Add(bubblun);
	scene.Add(bobblun);


}



int main(int, char* [])
{
	auto& serviceLocator = dae::ServiceLocator::GetInstance();
	serviceLocator.RegisterSoundSystem(std::make_unique<dae::MixerSoundSystem>());

	dae::Minigin engine("../Data/");
	engine.Run(load);

	return 0;
}

