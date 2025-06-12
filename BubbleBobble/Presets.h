#pragma once
#include "Scene.h"

#include "AnimationComponent.h"
#include "AttackComponent.h"
#include "BubbleComponent.h"
#include "ColliderComponent.h"
#include "MovementComponent.h"
#include "TextureComponent.h"
#include "HealthComponent.h"
#include "ZenChanAIComponent.h"

#include "InputManager.h"
#include "PlayerCommand.h"
#include "ServiceLocator.h"

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
			std::unique_ptr<dae::TextureComponent> playerTexture;
			if (isPlayerOne) playerTexture = std::make_unique<dae::TextureComponent>(*player, "Players/Bubblun.png");
			else playerTexture = std::make_unique<dae::TextureComponent>(*player, "Players/Bobblun.png");
			player->AddComponent(std::move(playerTexture));

			auto playerAnimation = std::make_unique<AnimationComponent>(*player,
			AnimationComponent::FrameData{ 16, 16, 7, 0.2f });
			player->AddComponent(std::move(playerAnimation));

			auto playerMovement = std::make_unique<dae::MovementComponent>(*player, 150.f, 400.f);
			player->AddComponent(std::move(playerMovement));

			auto playerAttack = std::make_unique<AttackComponent>(*player, isPlayerOne);
			player->AddComponent(std::move(playerAttack));

			auto playerHealth = std::make_unique<HealthComponent>(*player, 3);
			player->AddComponent(std::move(playerHealth));

			dae::ColliderComponent::ColliderInfo bubblunColliderInfo{
				dae::ColliderComponent::ColliderType::Solid,false, {48.f,48.f},{},
				static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player), static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Level)
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
			dae::ServiceLocator::GetInstance().GetPlayerSystem().RegisterPlayer(playerIdx, player.get());
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
			auto bubbleTexture = std::make_unique<dae::TextureComponent>(*bubble, "Players/Bubble.png");
			bubble->AddComponent(std::move(bubbleTexture));

			auto bubbleAnimation = std::make_unique<AnimationComponent>(*bubble,
				AnimationComponent::FrameData{ 16, 16, 3, 0.2f, rowIdx});
			bubble->AddComponent(std::move(bubbleAnimation));

			// COLLIDER
			auto colInfo = dae::ColliderComponent::ColliderInfo{
				dae::ColliderComponent::ColliderType::Trigger, false, { 48.f, 48.f },{},
				static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Projectile), static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Enemy)
			};
			auto bubbleCol = std::make_unique<dae::ColliderComponent>(*bubble,colInfo);
			bubble->AddComponent(std::move(bubbleCol));
			
			auto bubbleMovement = std::make_unique<dae::MovementComponent>(*bubble);
			bubbleMovement->SetUsesGravity(false);
			bubble->AddComponent(std::move(bubbleMovement));

			auto bubbleC = std::make_unique<BubbleComponent>(*bubble);
			bubbleC->Direction = direction;
			bubble->AddComponent(std::move(bubbleC));

			bubble->SetLocalPosition(pos);
			scene.Add(std::move(bubble));
		}
	};




	// ZEN-CHAN
	//----------------
	struct ZenChanPreset
	{
		std::vector<dae::GameObject> m_pPlayers;

		void SpawnZenChan(dae::Scene& scene, const glm::vec3 pos)
		{
			auto zenChan = std::make_unique<dae::GameObject>();


			// TEXTURE
			auto zenTexture = std::make_unique<dae::TextureComponent>(*zenChan, "Enemies/ZenChan.png");
			zenChan->AddComponent(std::move(zenTexture));

			// ANIMATION
			auto zenAnimation = std::make_unique<AnimationComponent>(*zenChan,
				AnimationComponent::FrameData{ 16, 16, 4, 0.2f });


			// COLLIDER
			auto colInfo = dae::ColliderComponent::ColliderInfo{
					dae::ColliderComponent::ColliderType::Solid,false, { 48.f, 48.f }, {},
					static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Enemy) , static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Level)
			};

			auto zenSolidCol = std::make_unique<dae::ColliderComponent>(*zenChan, colInfo);
			zenChan->AddComponent(std::move(zenSolidCol));

			colInfo.collisionFilter = static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player);
			auto zenTriggerCol = std::make_unique<dae::ColliderComponent>(*zenChan,colInfo);
			zenChan->AddComponent(std::move(zenTriggerCol));


			// MOVEMENT
			auto zenMovement = std::make_unique<dae::MovementComponent>(*zenChan, 100.f, 200.f);
			zenChan->AddComponent(std::move(zenMovement));

			// AI COMPONENT
			auto zenAI = std::make_unique<ZenChanAIComponent>(*zenChan);
			for (const auto& player : dae::ServiceLocator::GetInstance().GetPlayerSystem().GetPlayers())
			{
				if (player)
				{
					zenAI->AddPlayer(player);
				}
			}
			zenChan->AddComponent(std::move(zenAI));

				
			zenChan->SetLocalPosition(pos);
			scene.Add(std::move(zenChan));
		}
	};
}
