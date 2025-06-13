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

#pragma region MainMenu
	struct MainMenuPreset
	{
		bool isPlayerOne = true;
		void SpawnMainMenu(dae::Scene&) const
		{
			auto pressStart = std::make_unique<dae::GameObject>();
			auto font = dae::ResourceManager::GetInstance().LoadFont("font.ttf", 18);
			auto textComponent = std::make_unique<dae::TextComponent>(*pressStart, "BUBBLE BOBBLE", font);
			pressStart->AddComponent(std::move(textComponent));
			pressStart->SetLocalPosition({ 200,150 , 0 });
		}
		static void SetCommandsAndObservers(dae::Scene& scene)
		{
			// 1P START
			{
				auto pressStart = std::make_unique<dae::GameObject>();
				auto font = dae::ResourceManager::GetInstance().LoadFont("font.ttf", 18);
				auto textComponent = std::make_unique<dae::TextComponent>(*pressStart, "1P START", font);
				pressStart->AddComponent(std::move(textComponent));
				pressStart->SetLocalPosition({ 200,200 , 0 });
				auto uiComp = std::make_unique<dae::UIComponent>(*pressStart, [&]() {
					SwitchTo1P();
					});
				uiComp->Selected = true;
				pressStart->AddComponent(std::move(uiComp));

				auto& inputManager = dae::InputManager::GetInstance();
				inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_A, std::make_unique<PressButtonCommand>(pressStart.get()));
				inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_DPAD_DOWN, std::make_unique<NavigationDownCommand>(pressStart.get()));
				inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_DPAD_UP, std::make_unique<NavigationUpCommand>(pressStart.get()));


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
					SwitchTo2P();
					});
				pressStart2P->AddComponent(std::move(uiComp));
				auto& inputManager = dae::InputManager::GetInstance();
				inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_DPAD_DOWN, std::make_unique<NavigationDownCommand>(pressStart2P.get()));
				inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_DPAD_UP, std::make_unique<NavigationUpCommand>(pressStart2P.get()));
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
					SwitchToVersus();
					});
				pressStartVersus->AddComponent(std::move(uiComp));
				auto& inputManager = dae::InputManager::GetInstance();
				inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_DPAD_DOWN, std::make_unique<NavigationDownCommand>(pressStartVersus.get()));
				inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_DPAD_UP, std::make_unique<NavigationUpCommand>(pressStartVersus.get()));
				scene.Add(std::move(pressStartVersus));
			}

			// PASSWORD
			{
				auto pressPassword = std::make_unique<dae::GameObject>();
				auto font = dae::ResourceManager::GetInstance().LoadFont("font.ttf", 18);
				auto textComponent = std::make_unique<dae::TextComponent>(*pressPassword, "PASSWORD", font);
				pressPassword->AddComponent(std::move(textComponent));
				pressPassword->SetLocalPosition({ 200,350 , 0 });
				auto uiComp = std::make_unique<dae::UIComponent>(*pressPassword, [&]() {
					ShowPassword();
					});
				pressPassword->AddComponent(std::move(uiComp));
				auto& inputManager = dae::InputManager::GetInstance();
				inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_DPAD_DOWN, std::make_unique<NavigationDownCommand>(pressPassword.get()));
				inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_DPAD_UP, std::make_unique<NavigationUpCommand>(pressPassword.get()));
				scene.Add(std::move(pressPassword));
			}
		}


		static void SwitchTo1P()
		{
			ResetScene();

			auto& scene1_SinglePlayer = dae::SceneManager::GetInstance().CreateScene("Level1_SinglePlayer");
			auto level1_SinglePlayer = cat::Level(scene1_SinglePlayer, 1, "../Data/Levels/Level1.tmj",
				cat::Level::LevelGameMode::SinglePlayer);

			dae::SceneManager::GetInstance().SetActiveScene("Level1_SinglePlayer");
		}

		static void SwitchTo2P()
		{
			ResetScene();

			auto& scene1_Multiplayer = dae::SceneManager::GetInstance().CreateScene("Level1_Multiplayer");
			auto level1_Multiplayer = cat::Level(scene1_Multiplayer, 1, "../Data/Levels/Level1.tmj",
				cat::Level::LevelGameMode::Multiplayer);
			dae::SceneManager::GetInstance().SetActiveScene("Level1_Multiplayer");
		}

		static void SwitchToVersus()
		{
			ResetScene();
			auto& scene1_Versus = dae::SceneManager::GetInstance().CreateScene("Level1_Versus");
			auto level1_Versus = cat::Level(scene1_Versus, 1, "../Data/Levels/Level1.tmj",
				cat::Level::LevelGameMode::Versus);
			dae::SceneManager::GetInstance().SetActiveScene("Level1_Versus");
		}

		static void ShowPassword()
		{
			
		}
	};
#pragma endregion



#pragma region TitleScreen
	struct TitleScreenPreset
	{
		void SpawnTitleScreen(dae::Scene& scene) const 
		{
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
						AnimationComponent::FrameData{ 16, 16, 5, static_cast<float>(i % 4) / 5.f, i % 4 }
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
					AnimationComponent::FrameData{ 176, 142, 4, 0.2f });

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
				nintendo->SetLocalPosition({ 160, WINDOW_HEIGHT-100, 0 });
				scene.Add(std::move(nintendo));
			}


		}

		void SetCommandsAndObservers(dae::Scene& scene)
		{
			// START BTN
			{
				auto pressStart = std::make_unique<dae::GameObject>();

				auto font = dae::ResourceManager::GetInstance().LoadFont("font.ttf", 18);
				auto textComponent = std::make_unique<dae::TextComponent>(*pressStart, "PRESS A TO START", font);
				pressStart->AddComponent(std::move(textComponent));
				pressStart->SetLocalPosition({ 200, WINDOW_HEIGHT - 50, 0 });

				auto uiComp = std::make_unique<dae::UIComponent>(*pressStart, []() {
					TitleScreenPreset::SwitchToMainMenu();
					});
				uiComp->Selected = true; 
				pressStart->AddComponent(std::move(uiComp));

				auto& inputManager = dae::InputManager::GetInstance();
				inputManager.BindBtnCommand(0, XINPUT_GAMEPAD_A, std::make_unique<PressButtonCommand>(pressStart.get()));

				scene.Add(std::move(pressStart));
			}
		}

		static void SwitchToMainMenu()
		{
			ResetScene();
			auto& sceneMainMenu = dae::SceneManager::GetInstance().CreateScene("MainMenu");
			dae::SceneManager::GetInstance().SetActiveScene("MainMenu");

			cat::MainMenuPreset mainMenuPreset{};
			mainMenuPreset.SpawnMainMenu(sceneMainMenu);
			mainMenuPreset.SetCommandsAndObservers(sceneMainMenu);
		}
	};
#pragma endregion

}
