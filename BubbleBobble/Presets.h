#pragma once
#include "Scene.h"

#include "AnimationComponent.h"
#include "AttackComponent.h"
#include "BubbleComponent.h"
#include "ColliderComponent.h"
#include "MovementComponent.h"
#include "TextureComponent.h"
#include "HealthComponent.h"

#include "InputManager.h"
#include "PlayerCommand.h"

namespace cat
{
	// PLAYER
	//----------------
	struct PlayerPreset 
	{
		bool isPlayerOne;

		void SpawnPlayer(dae::Scene& scene, const glm::vec3 pos) const
		{
			auto player = std::make_unique<dae::GameObject>();
			int playerIdx = isPlayerOne ? 0 : 1;

			// COMPONENTS
			//----------------
			std::unique_ptr<TextureComponent> playerTexture;
			if (isPlayerOne) playerTexture = std::make_unique<TextureComponent>(*player, "Players/Bubblun.png");
			else playerTexture = std::make_unique<TextureComponent>(*player, "Players/Bobblun.png");
			player->AddComponent(std::move(playerTexture));

			auto playerAnimation = std::make_unique<AnimationComponent>(*player,
			AnimationComponent::FrameData{ 16, 16, 7, 0.2f });
			player->AddComponent(std::move(playerAnimation));

			auto playerMovement = std::make_unique<MovementComponent>(*player, 150.f, 400.f);
			player->AddComponent(std::move(playerMovement));

			auto playerAttack = std::make_unique<AttackComponent>(*player, isPlayerOne);
			player->AddComponent(std::move(playerAttack));

			auto playerHealth = std::make_unique<HealthComponent>(*player, 3);
			player->AddComponent(std::move(playerHealth));

			dae::ColliderComponent::ColliderInfo bubblunColliderInfo{
				dae::ColliderComponent::ColliderType::Solid,false, {48.f,48.f}
			};
			auto playerCollider = std::make_unique<dae::ColliderComponent>(*player, bubblunColliderInfo);
			player->AddComponent(std::move(playerCollider));

			// INPUT
			//----------------
			auto& inputManager = dae::InputManager::GetInstance();

			inputManager.BindBtnCommand(playerIdx, XINPUT_GAMEPAD_DPAD_LEFT, std::make_unique<cat::MoveLeftCommand>(cat::MoveLeftCommand(player.get())));
			inputManager.BindBtnCommand(playerIdx, XINPUT_GAMEPAD_DPAD_RIGHT, std::make_unique<cat::MoveRightCommand>(cat::MoveRightCommand(player.get())));
			inputManager.BindBtnCommand(playerIdx, XINPUT_GAMEPAD_A, std::make_unique<cat::JumpCommand>(cat::JumpCommand(player.get())));
			inputManager.BindBtnCommand(playerIdx, XINPUT_GAMEPAD_B, std::make_unique<cat::AttackCommand>(cat::AttackCommand(player.get()))); 

			// SPAWN
			//----------------
			player->SetLocalPosition(pos);
			scene.Add(std::move(player));
		}
	};


	// BUBBLE
	//----------------
	struct BubblePreset
	{
		bool isPlayerOne;
		glm::vec2 direction;

		void SpawnBubble(dae::Scene& scene, const glm::vec3 pos)
		{
			auto bubble = std::make_unique<dae::GameObject>();
			int rowIdx = isPlayerOne;

			// COMPONENTS
			//----------------
			auto bubbleTexture = std::make_unique<TextureComponent>(*bubble, "Players/Bubble.png");
			bubble->AddComponent(std::move(bubbleTexture));

			auto bubbleAnimation = std::make_unique<AnimationComponent>(*bubble,
				AnimationComponent::FrameData{ 16, 16, 3, 0.2f, rowIdx});
			bubble->AddComponent(std::move(bubbleAnimation));

			//auto bubbleCol = std::make_unique<dae::ColliderComponent>(*bubble,
			//	dae::ColliderComponent::ColliderInfo{ dae::ColliderComponent::ColliderType::Trigger, false, { 48.f, 48.f } });
			//bubble->AddComponent(std::move(bubbleCol));
			//
			auto bubbleMovement = std::make_unique<MovementComponent>(*bubble);
			bubbleMovement->SetUsesGravity(false);
			bubble->AddComponent(std::move(bubbleMovement));

			auto bubbleC = std::make_unique<BubbleComponent>(*bubble);
			bubbleC->Direction = direction;
			bubble->AddComponent(std::move(bubbleC));

			bubble->SetLocalPosition(pos);
			scene.Add(std::move(bubble));
		}
	};

	
}
