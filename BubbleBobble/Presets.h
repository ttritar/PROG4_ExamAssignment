#pragma once
#include "Scene.h"

#include "AnimationComponent.h"
#include "AttackComponent.h"
#include "BubbleComponent.h"
#include "MovementComponent.h"
#include "TextureComponent.h"
#include "HealthComponent.h"
#include "ColliderComponent.h"

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
			auto player = std::make_shared<dae::GameObject>();
			int playerIdx = isPlayerOne ? 0 : 1;

			// COMPONENTS
			//----------------
			std::shared_ptr<TextureComponent> playerTexture;
			if (isPlayerOne) playerTexture = std::make_shared<TextureComponent>(player, "Players/Bubblun.png");
			else playerTexture = std::make_shared<TextureComponent>(player, "Players/Bobblun.png");
			player->AddComponent(playerTexture);

			auto playerAnimation = std::make_shared<AnimationComponent>(player,
				AnimationComponent::FrameData{ 16, 16, 7, 0.2f });
			player->AddComponent(playerAnimation);

			auto playerMovement = std::make_shared<MovementComponent>(player, 150.f, 400.f);
			player->AddComponent(playerMovement);

			auto playerAttack = std::make_shared<AttackComponent>(player, isPlayerOne);
			player->AddComponent(playerAttack);

			auto playerHealth = std::make_shared<HealthComponent>(player, 3);
			player->AddComponent(playerHealth);

			cat::ColliderComponent::ColliderInfo bubblunColliderInfo{
				cat::ColliderComponent::ColliderType::Solid,false, {48.f,48.f}
			};
			auto playerCollider = std::make_shared<ColliderComponent>(player, bubblunColliderInfo);
			player->AddComponent(playerCollider);

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
			scene.Add(player);
		}
	};


	// BUBBLE
	//----------------
	struct BubblePreset
	{
		bool isBobblon;
		glm::vec2 direction;

		void SpawnBubble(dae::Scene& scene, const glm::vec3 pos)
		{
			auto bubble = std::make_shared<dae::GameObject>();
			int rowIdx = isBobblon ? 0 : 1;

			// COMPONENTS
			//----------------
			auto bubbleTexture = std::make_shared<TextureComponent>(bubble, "Players/Bubble.png");
			bubble->AddComponent(bubbleTexture);

			auto bubbleAnimation = std::make_shared<AnimationComponent>(bubble,
				AnimationComponent::FrameData{ 16, 16, 3, 0.2f, rowIdx});
			bubble->AddComponent(bubbleAnimation);

			auto bubbleCol = std::make_shared<ColliderComponent>(bubble,
				ColliderComponent::ColliderInfo{ ColliderComponent::ColliderType::Trigger, false, { 48.f, 48.f } });
			bubble->AddComponent(bubbleCol);

			auto bubbleMovement = std::make_shared<MovementComponent>(bubble);
			bubbleMovement->SetUsesGravity(false);
			bubble->AddComponent(bubbleMovement);

			auto bubbleC = std::make_shared<BubbleComponent>(bubble);
			bubbleC->Direction = direction;
			bubble->AddComponent(bubbleC);

			bubble->SetLocalPosition(pos);
			scene.Add(bubble);
		}
	};

	
}
