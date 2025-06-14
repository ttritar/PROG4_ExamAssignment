#include "ScenePresets.h"

#include "ResourceManager.h"
#include "Level.h"
#include "GeneralCommand.h"
#include "AnimationComponent.h"
#include "HighScore.h"
#include "MovementComponent.h"
#include "ScoreComponent.h"
#include "TextureComponent.h"
#include "WindowInfo.h"

#pragma region SceneSwitches

void cat::SwitchToNextLevel()
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
	else if (name == "Level2_SinglePlayer")
	{
		cat::SwitchToLVl3_1P();
	}
	else if (name == "Level2_Multiplayer")
	{
		cat::SwitchToLvl3_2P();
	}
	else if (name == "Level2_Versus")
	{
		cat::SwitchToLvl3_Versus();
	}

	else if (name == "Level3_SinglePlayer" ||
		name == "Level3_Multiplayer" ||
		name == "Level3_Versus")
	{
		cat::SwitchToPassword();
	}
}

void cat::SwitchToMainMenu()
{
	ResetScene();
	auto& sceneMainMenu = dae::SceneManager::GetInstance().CreateScene("MainMenu");
	dae::SceneManager::GetInstance().SetActiveScene("MainMenu");

	cat::MainMenuPreset mainMenuPreset{};
	mainMenuPreset.SpawnMainMenu(sceneMainMenu);
	mainMenuPreset.SetCommandsAndObservers(sceneMainMenu);
}

void cat::SwitchToPassword()
{
	ResetScene();
	auto& scene_password = dae::SceneManager::GetInstance().CreateScene("Password");
	dae::SceneManager::GetInstance().SetActiveScene("Password");
	PasswordPreset::SpawnPassword(scene_password);
}

void cat::SwitchToLVl1_1P()
{
	ResetScene();
	dae::ServiceLocator::GetInstance().GetSoundSystem().StopAllSounds();

	auto& scene1_SinglePlayer = dae::SceneManager::GetInstance().CreateScene("Level1_SinglePlayer");
	auto level1_SinglePlayer = cat::Level(scene1_SinglePlayer, 1, "Data/Levels/Level1.tmj",
		cat::Level::LevelGameMode::SinglePlayer);

	dae::SceneManager::GetInstance().SetActiveScene("Level1_SinglePlayer");
}

void cat::SwitchToLvl1_2P()
{
	ResetScene();
	dae::ServiceLocator::GetInstance().GetSoundSystem().StopAllSounds();

	auto& scene1_Multiplayer = dae::SceneManager::GetInstance().CreateScene("Level1_Multiplayer");
	auto level1_Multiplayer = cat::Level(scene1_Multiplayer, 1, "Data/Levels/Level1.tmj",
		cat::Level::LevelGameMode::Multiplayer);
	dae::SceneManager::GetInstance().SetActiveScene("Level1_Multiplayer");
}

void cat::SwitchToLvl1_Versus()
{
	ResetScene();
	dae::ServiceLocator::GetInstance().GetSoundSystem().StopAllSounds();

	auto& scene1_Versus = dae::SceneManager::GetInstance().CreateScene("Level1_Versus");
	auto level1_Versus = cat::Level(scene1_Versus, 1, "Data/Levels/Level1.tmj",
		cat::Level::LevelGameMode::Versus);
	dae::SceneManager::GetInstance().SetActiveScene("Level1_Versus");
}

void cat::SwitchToLVl2_1P()
{
	ResetScene();
	dae::ServiceLocator::GetInstance().GetSoundSystem().StopAllSounds();

	auto& scene1_SinglePlayer = dae::SceneManager::GetInstance().CreateScene("Level2_SinglePlayer");
	auto level1_SinglePlayer = cat::Level(scene1_SinglePlayer, 2, "Data/Levels/Level2.tmj",
		cat::Level::LevelGameMode::SinglePlayer);

	dae::SceneManager::GetInstance().SetActiveScene("Level2_SinglePlayer");
}

void cat::SwitchToLvl2_2P()
{
	ResetScene();
	dae::ServiceLocator::GetInstance().GetSoundSystem().StopAllSounds();

	auto& scene1_Multiplayer = dae::SceneManager::GetInstance().CreateScene("Level2_Multiplayer");
	auto level1_Multiplayer = cat::Level(scene1_Multiplayer, 2, "Data/Levels/Level2.tmj",
		cat::Level::LevelGameMode::Multiplayer);
	dae::SceneManager::GetInstance().SetActiveScene("Level2_Multiplayer");
}

void cat::SwitchToLvl2_Versus()
{
	ResetScene();
	dae::ServiceLocator::GetInstance().GetSoundSystem().StopAllSounds();
	auto& scene1_Versus = dae::SceneManager::GetInstance().CreateScene("Level2_Versus");
	auto level1_Versus = cat::Level(scene1_Versus, 2, "Data/Levels/Level2.tmj",
		cat::Level::LevelGameMode::Versus);
	dae::SceneManager::GetInstance().SetActiveScene("Level2_Versus");
}

void cat::SwitchToLVl3_1P()
{
	ResetScene();
	dae::ServiceLocator::GetInstance().GetSoundSystem().StopAllSounds();

	auto& scene1_SinglePlayer = dae::SceneManager::GetInstance().CreateScene("Level3_SinglePlayer");
	auto level1_SinglePlayer = cat::Level(scene1_SinglePlayer, 2, "Data/Levels/Level3.tmj",
		cat::Level::LevelGameMode::SinglePlayer);

	dae::SceneManager::GetInstance().SetActiveScene("Level3_SinglePlayer");
}

void cat::SwitchToLvl3_2P()
{
	ResetScene();
	dae::ServiceLocator::GetInstance().GetSoundSystem().StopAllSounds();

	auto& scene1_Multiplayer = dae::SceneManager::GetInstance().CreateScene("Level3_Multiplayer");
	auto level1_Multiplayer = cat::Level(scene1_Multiplayer, 2, "Data/Levels/Level3.tmj",
		cat::Level::LevelGameMode::Multiplayer);
	dae::SceneManager::GetInstance().SetActiveScene("Level3_Multiplayer");
}

void cat::SwitchToLvl3_Versus()
{
	ResetScene();
	dae::ServiceLocator::GetInstance().GetSoundSystem().StopAllSounds();
	auto& scene1_Versus = dae::SceneManager::GetInstance().CreateScene("Level3_Versus");
	auto level1_Versus = cat::Level(scene1_Versus, 2, "Data/Levels/Level3.tmj",
		cat::Level::LevelGameMode::Versus);
	dae::SceneManager::GetInstance().SetActiveScene("Level3_Versus");
}

#pragma endregion


#pragma region Password
void cat::PasswordPreset::SpawnPassword(dae::Scene& scene)
{
	auto password = std::make_unique<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("font.ttf", 18);
	auto textComponent = std::make_unique<dae::TextComponent>(*password, "PASSWORD:", font);
	password->AddComponent(std::move(textComponent));
	password->SetLocalPosition({ 100, 100, 0 });
	scene.Add(std::move(password));

	char* passwordChars = new char[5];
	//--- LETTERS ---
	{
		// 1
		{
			auto letter = std::make_unique<dae::GameObject>();

			passwordChars[0] = 'A';
			std::string letterStr(1, passwordChars[0]);
			auto letterTxtComponent = std::make_unique<dae::TextComponent>(*letter, letterStr, font);

			letter->AddComponent(std::move(letterTxtComponent));

			auto uiComponent = std::make_unique<dae::UIComponent>(*letter, [passwordChars, letterPtr = letter.get()]() mutable {
				passwordChars[0]++;
				if (passwordChars[0] > 'Z') passwordChars[0] = 'A';
				letterPtr->GetComponent<dae::TextComponent>()->SetText(std::string(1, passwordChars[0]));
				});
			dae::ServiceLocator::GetInstance().GetUIInputSystem().SetSelectedUIComponent(uiComponent.get());
			letter->AddComponent(std::move(uiComponent));

			letter->SetLocalPosition({ 100, 150, 0 });
			scene.Add(std::move(letter));
		}

		// 2
		{
			auto letter = std::make_unique<dae::GameObject>();

			passwordChars[1] = 'A';
			std::string letterStr(1, passwordChars[0]);
			auto letterTxtComponent = std::make_unique<dae::TextComponent>(*letter, letterStr, font);

			letter->AddComponent(std::move(letterTxtComponent));

			auto uiComponent = std::make_unique<dae::UIComponent>(*letter, [passwordChars, letterPtr = letter.get()]() mutable {
				passwordChars[1]++;
				if (passwordChars[1] > 'Z') passwordChars[0] = 'A';
				letterPtr->GetComponent<dae::TextComponent>()->SetText(std::string(1, passwordChars[1]));
				});
			letter->AddComponent(std::move(uiComponent));

			letter->SetLocalPosition({ 125, 150, 0 });
			scene.Add(std::move(letter));
		}

		// 3
		{
			auto letter = std::make_unique<dae::GameObject>();

			passwordChars[2] = 'A';
			std::string letterStr(1, passwordChars[2]);
			auto letterTxtComponent = std::make_unique<dae::TextComponent>(*letter, letterStr, font);

			letter->AddComponent(std::move(letterTxtComponent));

			auto uiComponent = std::make_unique<dae::UIComponent>(*letter, [passwordChars, letterPtr = letter.get()]() mutable {
				passwordChars[2]++;
				if (passwordChars[2] > 'Z') passwordChars[2] = 'A';
				letterPtr->GetComponent<dae::TextComponent>()->SetText(std::string(1, passwordChars[2]));
				});
			letter->AddComponent(std::move(uiComponent));

			letter->SetLocalPosition({ 150, 150, 0 });
			scene.Add(std::move(letter));
		}

		// 4
		{
			auto letter = std::make_unique<dae::GameObject>();

			passwordChars[3] = 'A';
			std::string letterStr(1, passwordChars[3]);
			auto letterTxtComponent = std::make_unique<dae::TextComponent>(*letter, letterStr, font);

			letter->AddComponent(std::move(letterTxtComponent));

			auto uiComponent = std::make_unique<dae::UIComponent>(*letter, [passwordChars, letterPtr = letter.get()]() mutable {
				passwordChars[3]++;
				if (passwordChars[3] > 'Z') passwordChars[3] = 'A';
				letterPtr->GetComponent<dae::TextComponent>()->SetText(std::string(1, passwordChars[3]));
				});
			letter->AddComponent(std::move(uiComponent));

			letter->SetLocalPosition({ 175, 150, 0 });
			scene.Add(std::move(letter));
		}

		// 5
		{
			auto letter = std::make_unique<dae::GameObject>();

			passwordChars[4] = 'A';
			std::string letterStr(1, passwordChars[4]);
			auto letterTxtComponent = std::make_unique<dae::TextComponent>(*letter, letterStr, font);

			letter->AddComponent(std::move(letterTxtComponent));

			auto uiComponent = std::make_unique<dae::UIComponent>(*letter, [passwordChars, letterPtr = letter.get()]() mutable {
				passwordChars[4]++;
				if (passwordChars[3] > 'Z') passwordChars[4] = 'A';
				letterPtr->GetComponent<dae::TextComponent>()->SetText(std::string(1, passwordChars[4]));
				});
			letter->AddComponent(std::move(uiComponent));

			letter->SetLocalPosition({200, 150, 0 });
			scene.Add(std::move(letter));
		}
	}

	//--- OTHER HIGHSCORES ---
	{
		auto instr = std::make_unique<dae::GameObject>();;
		auto smallfont = dae::ResourceManager::GetInstance().LoadFont("font.ttf", 12);
		auto instrTextComponent = std::make_unique<dae::TextComponent>(*instr, "PRESS B TO SAVE AND A TO CHANGE THE LETTERS!", smallfont);
		instr->AddComponent(std::move(instrTextComponent));
		instr->SetLocalPosition({ 50, 500, 0 });
		scene.Add(std::move(instr));

		auto highscore = std::make_unique<dae::GameObject>();
		auto hsTxtComp = std::make_unique<dae::TextComponent>(*highscore, "HIGHSCORES:", font);
		highscore->AddComponent(std::move(hsTxtComp));
		highscore->SetLocalPosition({ 150, 200, 0 });
		scene.Add(std::move(highscore));

		auto othersFont = dae::ResourceManager::GetInstance().LoadFont("font.ttf", 14);
		auto hss = HighScore::ReadFromFile();
		for (int i =0; i< hss.size() ; i++)
		{
			auto others = std::make_unique<dae::GameObject>();
			others->SetLocalPosition({ 200, 260 + i * 20, 0 });
			std::string othersText = hss[i].playerName + ": " + std::to_string(hss[i].score);
			auto othersTextComponent = std::make_unique<dae::TextComponent>(*others, othersText, othersFont);
			others->AddComponent(std::move(othersTextComponent));
			scene.Add(std::move(others));
		}
	}

	auto uiController = std::make_unique<dae::GameObject>();
	auto& inputManager = dae::InputManager::GetInstance();
	
	inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_DPAD_RIGHT, std::make_unique<NavigationNextCommand>(uiController.get()));
	inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_DPAD_LEFT, std::make_unique<NavigationPreviousCommand>(uiController.get()));
	inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_A, std::make_unique<PressButtonCommand>(uiController.get()));
	inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_B, std::make_unique<CustomUICommand>(uiController.get(), [passwordChars, &scene, &inputManager]() {

		// save the highscore 
		HighScore{
			.playerName = std::string(passwordChars),
			.score = ScoreComponent::GetCurrentScore()
		}.WriteToFile();

		auto feedback = std::make_unique<dae::GameObject>();
		auto font = dae::ResourceManager::GetInstance().LoadFont("font.ttf", 14);
		auto textComponent = std::make_unique<dae::TextComponent>(*feedback, "SUCCESFULLY ADDED THE HIGHSCORE!", font);
		feedback->AddComponent(std::move(textComponent));
		feedback->SetLocalPosition({ 200, 225, 0 });
		scene.Add(std::move(feedback));

		inputManager.UnbindAllBtnCommands(0);

		}));


	inputManager.BindKeyCommand( SDLK_RIGHT, std::make_unique<NavigationNextCommand>(uiController.get()));
	inputManager.BindKeyCommand( SDLK_LEFT, std::make_unique<NavigationPreviousCommand>(uiController.get()));
	inputManager.BindKeyCommand(SDLK_d, std::make_unique<NavigationNextCommand>(uiController.get()));
	inputManager.BindKeyCommand(SDLK_a, std::make_unique<NavigationPreviousCommand>(uiController.get()));
	inputManager.BindKeyCommand(SDLK_RETURN, std::make_unique<PressButtonCommand>(uiController.get()));
	inputManager.BindKeyCommand(SDLK_SPACE, std::make_unique<PressButtonCommand>(uiController.get()));
	inputManager.BindKeyCommand(SDLK_BACKSPACE, std::make_unique<CustomUICommand>(uiController.get(), [passwordChars, &scene, &inputManager]() {

		// save the highscore 
		HighScore{
			.playerName = std::string(passwordChars),
			.score = ScoreComponent::GetCurrentScore()
		}.WriteToFile();

		auto feedback = std::make_unique<dae::GameObject>();
		auto font = dae::ResourceManager::GetInstance().LoadFont("font.ttf", 14);
		auto textComponent = std::make_unique<dae::TextComponent>(*feedback, "SUCCESFULLY ADDED THE HIGHSCORE!", font);
		feedback->AddComponent(std::move(textComponent));
		feedback->SetLocalPosition({ 200, 225, 0 });
		scene.Add(std::move(feedback));

		inputManager.UnbindAllBtnCommands(0);

		}));

	scene.Add(std::move(uiController));

	auto controller = std::make_unique<dae::GameObject>();
	inputManager.BindKeyCommand(SDLK_F2, std::make_unique<cat::MuteCommand>(controller.get()));
	scene.Add(std::move(controller));

}
#pragma endregion

#pragma region MainMenu
void cat::MainMenuPreset::SpawnMainMenu(dae::Scene& scene) const
{
	auto pressStart = std::make_unique<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("font.ttf", 18);
	auto textComponent = std::make_unique<dae::TextComponent>(*pressStart, "BUBBLE BOBBLE", font);
	pressStart->AddComponent(std::move(textComponent));
	pressStart->SetLocalPosition({ 200,150 , 0 });
	scene.Add(std::move(pressStart));
}

void cat::MainMenuPreset::SetCommandsAndObservers(dae::Scene& scene)
{
	// 1P START
	{
		auto pressStart = std::make_unique<dae::GameObject>();
		auto font = dae::ResourceManager::GetInstance().LoadFont("font.ttf", 18);
		auto textComponent = std::make_unique<dae::TextComponent>(*pressStart, "1P START", font);
		pressStart->AddComponent(std::move(textComponent));
		pressStart->SetLocalPosition({ 200,200 , 0 });
		auto uiComp = std::make_unique<dae::UIComponent>(*pressStart, [&]() {
			SwitchToLVl1_1P();
		});
		dae::ServiceLocator::GetInstance().GetUIInputSystem().SetSelectedUIComponent(uiComp.get());
		pressStart->AddComponent(std::move(uiComp));



		scene.Add(std::move(pressStart));
	}

	// 2P START
	{
		auto pressStart2P = std::make_unique<dae::GameObject>();
		auto font = dae::ResourceManager::GetInstance().LoadFont("font.ttf", 18);
		auto textComponent = std::make_unique<dae::TextComponent>(*pressStart2P, "2P START", font);
		pressStart2P->AddComponent(std::move(textComponent));
		pressStart2P->SetLocalPosition({ 200,250 , 0 });
		auto uiComp = std::make_unique<dae::UIComponent>(*pressStart2P, [&]() {
			SwitchToLvl1_2P();
		});
		pressStart2P->AddComponent(std::move(uiComp));
		scene.Add(std::move(pressStart2P));
	}

	// VERSUS START
	{
		auto pressStartVersus = std::make_unique<dae::GameObject>();
		auto font = dae::ResourceManager::GetInstance().LoadFont("font.ttf", 18);
		auto textComponent = std::make_unique<dae::TextComponent>(*pressStartVersus, "VERSUS START", font);
		pressStartVersus->AddComponent(std::move(textComponent));
		pressStartVersus->SetLocalPosition({ 200,300 , 0 });
		auto uiComp = std::make_unique<dae::UIComponent>(*pressStartVersus, [&]() {
			SwitchToLvl1_Versus();
		});
		pressStartVersus->AddComponent(std::move(uiComp));
		scene.Add(std::move(pressStartVersus));
	}

	//// PASSWORD
	//{
	//	auto pressPassword = std::make_unique<dae::GameObject>();
	//	auto font = dae::ResourceManager::GetInstance().LoadFont("font.ttf", 18);
	//	auto textComponent = std::make_unique<dae::TextComponent>(*pressPassword, "PASSWORD", font);
	//	pressPassword->AddComponent(std::move(textComponent));
	//	pressPassword->SetLocalPosition({ 200,350 , 0 });
	//	auto uiComp = std::make_unique<dae::UIComponent>(*pressPassword, [&]() {
	//		SwitchToPassword();
	//	});
	//	pressPassword->AddComponent(std::move(uiComp));
	//	scene.Add(std::move(pressPassword));
	//}


	auto uiController = std::make_unique<dae::GameObject>();
	auto& inputManager = dae::InputManager::GetInstance();
	inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_DPAD_DOWN, std::make_unique<NavigationNextCommand>(uiController.get()));
	inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_DPAD_UP, std::make_unique<NavigationPreviousCommand>(uiController.get()));
	inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_A, std::make_unique<PressButtonCommand>(uiController.get()));

	inputManager.BindKeyCommand( SDLK_DOWN, std::make_unique<NavigationNextCommand>(uiController.get()));
	inputManager.BindKeyCommand( SDLK_UP, std::make_unique<NavigationPreviousCommand>(uiController.get()));
	inputManager.BindKeyCommand(SDLK_s, std::make_unique<NavigationNextCommand>(uiController.get()));
	inputManager.BindKeyCommand(SDLK_w, std::make_unique<NavigationPreviousCommand>(uiController.get()));
	inputManager.BindKeyCommand( SDLK_RETURN, std::make_unique<PressButtonCommand>(uiController.get()));
	inputManager.BindKeyCommand(SDLK_SPACE, std::make_unique<PressButtonCommand>(uiController.get()));

	scene.Add(std::move(uiController));

	auto controller = std::make_unique<dae::GameObject>();
	inputManager.BindKeyCommand(SDLK_F2, std::make_unique<cat::MuteCommand>(controller.get()));
	scene.Add(std::move(controller));
}
#pragma endregion

#pragma region TitleScreen
void cat::TitleScreenPreset::SpawnTitleScreen(dae::Scene& scene) const
{
	// load title screen music
	dae::sound_id hash = static_cast<dae::sound_id>(dae::make_sdbm_hash("Title"));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(hash, "Data/UI/TitleTheme.mp3");
	dae::ServiceLocator::GetInstance().GetSoundSystem().Play(hash,100);

	// BUBBLES
	{
		// random movement bubbles
		for (int i = 0; i < 100; ++i)
		{
			auto bubble = std::make_unique<dae::GameObject>();

			auto textureComponent = std::make_unique<dae::TextureComponent>(*bubble, "UI/Bubbles.png");
			textureComponent->Scale = 2.f;
			bubble->AddComponent(std::move(textureComponent));

			auto animComponent = std::make_unique<AnimationComponent>(*bubble,
				AnimationComponent::FrameAnimationData{ 16, 16, 5, static_cast<float>(i % 4) / 5.f, i % 4 }
			);
			bubble->AddComponent(std::move(animComponent));

			auto moveComponent = std::make_unique<dae::MovementComponent>(*bubble, 50.f, 100.f);
			moveComponent->SetUsesGravity(false);
			float angle = static_cast<float>(rand() % 360) * (3.14159f / 180.f);
			moveComponent->Velocity = glm::vec2{ cosf(angle) * 50.f, sinf(angle) * 50.f };
			bubble->AddComponent(std::move(moveComponent));

			bubble->SetLocalPosition({ static_cast<float>(rand() % WINDOW_WIDTH), static_cast<float>(rand() % WINDOW_HEIGHT), 0 });
			scene.Add(std::move(bubble));
		}

		auto opOverlay = std::make_unique<dae::GameObject>();
		auto opTextureComponent = std::make_unique<dae::TextureComponent>(*opOverlay, "UI/OverlayOpacity50.png");
		opOverlay->AddComponent(std::move(opTextureComponent));
		scene.Add(std::move(opOverlay));

	}


	// TITLE 
	{
		auto title = std::make_unique<dae::GameObject>();

		auto textureComponent = std::make_unique<dae::TextureComponent>(*title, "UI/Title.png");
		textureComponent->Scale = 2.f;
		title->AddComponent(std::move(textureComponent));

		auto animComponent = std::make_unique<AnimationComponent>(*title,
			AnimationComponent::FrameAnimationData{ 176, 142, 4, 0.2f });

		title->SetLocalPosition({ 200, 100, 0 });
		scene.Add(std::move(title));
	}


	// NINTENDO LICENSE BECAUSE ILL GET SHOT OTHERWISE
	{
		auto font = dae::ResourceManager::GetInstance().LoadFont("font.ttf", 20);

		auto taito = std::make_unique<dae::GameObject>();
		auto textComponent = std::make_unique<dae::TextComponent>(*taito, "@ 1990 TAITO CORPORATION", font);
		taito->AddComponent(std::move(textComponent));
		taito->SetLocalPosition({ 120, WINDOW_HEIGHT - 150, 0 });
		scene.Add(std::move(taito));

		auto nintendo = std::make_unique<dae::GameObject>();
		auto textComponent2 = std::make_unique<dae::TextComponent>(*nintendo, "LICENSED BY NINTENDO", font);
		nintendo->AddComponent(std::move(textComponent2));
		nintendo->SetLocalPosition({ 160, WINDOW_HEIGHT - 100, 0 });
		scene.Add(std::move(nintendo));
	}


}

void cat::TitleScreenPreset::SetCommandsAndObservers(dae::Scene& scene)
{
	// START BTN
	{
		auto pressStart = std::make_unique<dae::GameObject>();

		auto font = dae::ResourceManager::GetInstance().LoadFont("font.ttf", 18);
		auto textComponent = std::make_unique<dae::TextComponent>(*pressStart, "PRESS A TO START", font);
		pressStart->AddComponent(std::move(textComponent));
		pressStart->SetLocalPosition({ 200, WINDOW_HEIGHT - 50, 0 });

		auto uiComp = std::make_unique<dae::UIComponent>(*pressStart, []() {
			SwitchToMainMenu();
		});
		uiComp->Selected = true; 
		pressStart->AddComponent(std::move(uiComp));

		auto& inputManager = dae::InputManager::GetInstance();
		inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_A, std::make_unique<PressButtonCommand>(pressStart.get()));
		inputManager.BindKeyCommand(SDLK_RETURN, std::make_unique<PressButtonCommand>(pressStart.get()));
		inputManager.BindKeyCommand(SDLK_SPACE, std::make_unique<PressButtonCommand>(pressStart.get()));
		scene.Add(std::move(pressStart));

		auto controller = std::make_unique<dae::GameObject>();
		inputManager.BindKeyCommand(SDLK_F2, std::make_unique<cat::MuteCommand>(controller.get()));
		scene.Add(std::move(controller));
	}
}

#pragma endregion
