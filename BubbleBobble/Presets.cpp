#include "Presets.h"

#include "HealthComponent.h"
#include "ZenChanAIComponent.h"
#include "HealthObserverComponent.h"
#include "PlayerSoundObserverComponent.h"
#include "ScoreObserverComponent.h"

#include "CollisionObserverComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "AttackComponent.h"

#include "InputManager.h"
#include "PlayerCommand.h"
#include "ScoreComponent.h"
#include "ServiceLocator.h"
#include "WindowInfo.h"
#include "BoulderComponent.h"
#include "Level.h"

void cat::PlayerPreset::SpawnPlayer(dae::Scene& scene, const glm::vec3 pos) const
{

	auto player = std::make_unique<dae::GameObject>();
	int playerIdx = isPlayerOne ? 0 : 1;

	// COMPONENTS
	//----------------
	std::unique_ptr<dae::TextureComponent> playerTexture;
	if (isPlayerOne) playerTexture = std::make_unique<dae::TextureComponent>(*player, "Players/Bubblun.png");
	else playerTexture = std::make_unique<dae::TextureComponent>(*player, "Players/Bobblun.png");
	player->AddComponent(std::move(playerTexture));

	auto playerAnimation = std::make_unique<AnimationComponent>(*player,AnimationComponent::FrameAnimationData{ 16, 16, 7, 0.2f });
	player->AddComponent(std::move(playerAnimation));

	auto playerMovement = std::make_unique<dae::MovementComponent>(*player, 150.f, 400.f);
	player->AddComponent(std::move(playerMovement));

	auto playerAttack = std::make_unique<AttackComponent>(*player, isPlayerOne);
	player->AddComponent(std::move(playerAttack));

	auto playerHealth = std::make_unique<HealthComponent>(*player);
	player->AddComponent(std::move(playerHealth));

	auto playerScore = std::make_unique<ScoreComponent>(*player);
	player->AddComponent(std::move(playerScore));

	dae::ColliderComponent::ColliderInfo bubblunColliderInfo{
		dae::ColliderComponent::ColliderType::Solid,false, {40.f,40.f},{},
		static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player),
		static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Level)
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


	// OBSERVERS
	//----------------
	auto playerSoundObserver = std::make_unique<PlayerSoundObserverComponent>(*player);
	player->AddObserver(playerSoundObserver.get());
	player->AddComponent(std::move(playerSoundObserver));

	auto itemCollisionObserver = std::make_unique<PlayerCollisionObserverComponent>(*player);
	player->AddObserver(itemCollisionObserver.get());
	player->AddComponent(std::move(itemCollisionObserver));


	auto fontUI = dae::ResourceManager::GetInstance().LoadFont("font.ttf", 20);
	// SCORE TEXT
	{
		auto score = std::make_unique<dae::GameObject>();
		score->SetLocalPosition({ 100,20,0 });
		auto textScore = std::make_unique<dae::TextComponent>(*score, std::to_string(ScoreComponent::GetCurrentScore()), fontUI);
		score->AddComponent(std::move(textScore));
		auto scoreObserver = std::make_unique<ScoreObserverComponent>(*score);
		player->AddObserver(scoreObserver.get());
		score->AddComponent(std::move(scoreObserver));
		scene.Add(std::move(score));
	}
	// HEALTH TEXT
	{
		auto health = std::make_unique<dae::GameObject>();
		health->SetLocalPosition({ 50,WINDOW_HEIGHT - 70,0 });
		auto textHealth = std::make_unique<dae::TextComponent>(*health, std::to_string(HealthComponent::GetCurrentHealth()), fontUI);
		health->AddComponent(std::move(textHealth));
		auto healthObserver = std::make_unique<HealthObserverComponent>(*health);
		player->AddObserver(healthObserver.get());
		health->AddComponent(std::move(healthObserver));
		scene.Add(std::move(health));
	}


	// SPAWN
	//----------------
	player->SetLocalPosition(pos);
	dae::ServiceLocator::GetInstance().GetPlayerSystem().RegisterPlayer(scene.GetName(), playerIdx, player.get());
	scene.Add(std::move(player));
}

void cat::PLayerMaitaPreset::SpawnPlayer(dae::Scene& scene, const glm::vec3 pos) const
{
	auto player = std::make_unique<dae::GameObject>();
	int playerIdx = isPlayerOne ? 0 : 1;

	// COMPONENTS
	//----------------
	auto playerTexture = std::make_unique<dae::TextureComponent>(*player, "Enemies/Maita.png");
	player->AddComponent(std::move(playerTexture));

	auto playerAnimation = std::make_unique<AnimationComponent>(*player, AnimationComponent::FrameAnimationData{ 16, 16, 5, 0.2f });
	player->AddComponent(std::move(playerAnimation));

	auto playerMovement = std::make_unique<dae::MovementComponent>(*player, 150.f, 400.f);
	player->AddComponent(std::move(playerMovement));

	auto playerAttack = std::make_unique<AttackComponent>(*player, 1, AttackComponent::Boulder);
	player->AddComponent(std::move(playerAttack));

	dae::ColliderComponent::ColliderInfo playerColliderInfo{
		dae::ColliderComponent::ColliderType::Solid,false, {40.f,40.f},{},
		static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Enemy),
		 static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player) | static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Level)
	};
	auto playerCollider = std::make_unique<dae::ColliderComponent>(*player, playerColliderInfo);
	player->AddComponent(std::move(playerCollider));

	// INPUT
	//----------------
	auto& inputManager = dae::InputManager::GetInstance();

	inputManager.BindBtnCommand(playerIdx, XINPUT_GAMEPAD_DPAD_LEFT, std::make_unique<cat::MoveLeftCommand>(cat::MoveLeftCommand(player.get())));
	inputManager.BindBtnCommand(playerIdx, XINPUT_GAMEPAD_DPAD_RIGHT, std::make_unique<cat::MoveRightCommand>(cat::MoveRightCommand(player.get())));
	inputManager.BindBtnCommand(playerIdx, XINPUT_GAMEPAD_A, std::make_unique<cat::JumpCommand>(cat::JumpCommand(player.get())));
	inputManager.BindBtnCommand(playerIdx, XINPUT_GAMEPAD_B, std::make_unique<cat::AttackCommand>(cat::AttackCommand(player.get())));


	// OBSERVERS
	//----------------
	auto playerCollisionObserver = std::make_unique<EnemyCollisionObserverComponent>(*player);
	player->AddObserver(playerCollisionObserver.get());
	player->AddComponent(std::move(playerCollisionObserver));

	// SPAWN
	//----------------
	player->SetLocalPosition(pos);
	dae::ServiceLocator::GetInstance().GetPlayerSystem().RegisterPlayer(scene.GetName(), playerIdx, player.get());
	scene.Add(std::move(player));
}

void cat::BubblePreset::SpawnBubble(dae::Scene& scene, const glm::vec3 pos) const
{
	auto bubble = std::make_unique<dae::GameObject>();
	int rowIdx = isPlayerOne;

	// COMPONENTS
	//----------------
	auto bubbleTexture = std::make_unique<dae::TextureComponent>(*bubble, "Players/Bubble.png");
	bubble->AddComponent(std::move(bubbleTexture));

	auto bubbleAnimation = std::make_unique<AnimationComponent>(*bubble,
		AnimationComponent::FrameAnimationData{ 16, 16, 3, 0.2f, rowIdx});
	bubble->AddComponent(std::move(bubbleAnimation));

	// MOVEMENT			
	auto bubbleMovement = std::make_unique<dae::MovementComponent>(*bubble);
	bubbleMovement->SetUsesGravity(false);
	bubble->AddComponent(std::move(bubbleMovement));

	if (type == BubbleComponent::TrappedEnemyType::None)
	{
		auto bubbleC = std::make_unique<BubbleComponent>(*bubble);
		bubbleC->Direction = direction;
		bubble->AddComponent(std::move(bubbleC));
	}
	else
	{
		auto bubbleC = std::make_unique<BubbleComponent>(*bubble,type);
		bubbleC->Direction = direction;
		bubble->AddComponent(std::move(bubbleC));
	}

	// COLLIDER
	auto colInfo = dae::ColliderComponent::ColliderInfo{
		dae::ColliderComponent::ColliderType::Solid, false, { 48.f, 48.f },{},
		static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Bubble),
		static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Enemy) | static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player)
	};
	auto bubbleCol = std::make_unique<dae::ColliderComponent>(*bubble, colInfo);
	bubble->AddComponent(std::move(bubbleCol));


	bubble->SetLocalPosition({pos.x + direction.x*100,pos.y,pos.z});
	scene.Add(std::move(bubble));
}


void cat::BoulderPreset::SpawnBoulder(dae::Scene& scene, const glm::vec3 pos) const
{
	auto boulder = std::make_unique<dae::GameObject>();

	// COMPONENTS
	//----------------
	auto boulderTexture = std::make_unique<dae::TextureComponent>(*boulder, "Enemies/Boulder.png");
	boulder->AddComponent(std::move(boulderTexture));

	auto boulderAnimation = std::make_unique<AnimationComponent>(*boulder,
		AnimationComponent::FrameAnimationData{ 16, 16, 7, 0.3f, 0 });
	boulder->AddComponent(std::move(boulderAnimation));

	// MOVEMENT			
	auto boulderMovement = std::make_unique<dae::MovementComponent>(*boulder,300.f);
	boulderMovement->SetUsesGravity(false);
	boulder->AddComponent(std::move(boulderMovement));

	auto boulderC = std::make_unique<BoulderComponent>(*boulder);
	boulderC->Direction = direction;
	boulder->AddComponent(std::move(boulderC));

	// COLLIDER
	auto colInfo = dae::ColliderComponent::ColliderInfo{
		dae::ColliderComponent::ColliderType::Solid, false, { 48.f, 48.f },{},
		static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Enemy),
		static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player)
	};
	auto boulderCol = std::make_unique<dae::ColliderComponent>(*boulder, colInfo);
	boulder->AddComponent(std::move(boulderCol));


	auto boulderCollisionObserver = std::make_unique<EnemyCollisionObserverComponent>(*boulder);
	boulder->AddObserver(boulderCollisionObserver.get());
	boulder->AddComponent(std::move(boulderCollisionObserver));


	boulder->SetLocalPosition(pos);
	scene.Add(std::move(boulder));
}


void cat::ZenChanPreset::SpawnZenChan(dae::Scene& scene, const glm::vec3 pos)
{
	auto zenChan = std::make_unique<dae::GameObject>();


	// TEXTURE
	auto zenTexture = std::make_unique<dae::TextureComponent>(*zenChan, "Enemies/ZenChan.png");
	zenChan->AddComponent(std::move(zenTexture));

	// ANIMATION
	auto zenAnimation = std::make_unique<AnimationComponent>(*zenChan,
	                                                         AnimationComponent::FrameAnimationData{ 16, 16, 4, 0.2f });
	zenChan->AddComponent(std::move(zenAnimation));

	// MOVEMENT
	auto zenMovement = std::make_unique<dae::MovementComponent>(*zenChan, 100.f, 400.f);
	zenChan->AddComponent(std::move(zenMovement));


	// COLLIDER
	/*	dae::ColliderComponent::ColliderInfo colTriggerInfo{
			dae::ColliderComponent::ColliderType::Trigger,false, {80.f,80.f},{-16.f,-16.f},
				static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Enemy),
				static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player)
			};
			auto zenTriggerCol = std::make_unique<dae::ColliderComponent>(*zenChan, colTriggerInfo);
			zenChan->AddComponent(std::move(zenTriggerCol));*/

	dae::ColliderComponent::ColliderInfo colSolidInfo{
		dae::ColliderComponent::ColliderType::Solid,false, {40.f,40.f},{},
		static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Enemy),
		static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Level) | static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player)
	};
	auto zenSolidCol = std::make_unique<dae::ColliderComponent>(*zenChan, colSolidInfo);
	zenChan->AddComponent(std::move(zenSolidCol));

	// AI COMPONENT
	auto zenAI = std::make_unique<ZenChanAIComponent>(*zenChan);
	zenChan->AddComponent(std::move(zenAI));


	// OBSERVERS
	//-----------------
	auto zenCollisionObserver = std::make_unique<EnemyCollisionObserverComponent>(*zenChan);
	zenChan->AddObserver(zenCollisionObserver.get());
	zenChan->AddComponent(std::move(zenCollisionObserver));

				
	zenChan->SetLocalPosition(pos);
	scene.Add(std::move(zenChan));
}

void cat::ItemPreset::SpawnItem(dae::Scene& scene, const glm::vec3 pos)
{
	auto item = std::make_unique<dae::GameObject>();

	glm::vec2 initialVelocity{
		(rand() % 2 == 0 ? -1.f : 1.f) * (50.f + rand() % 50),
		-150.f // Upward velocity
	};
	auto movement = std::make_unique<dae::MovementComponent>(*item, initialVelocity.x, initialVelocity.y);
	movement->Jump();
	movement->SetUsesGravity(true);
	item->AddComponent(std::move(movement));

	auto texture = std::make_unique<dae::TextureComponent>(*item, "Enemies/Items.png");
	int itemIdx = rand() % 9;
	texture->SrcRect={
		static_cast<int>(16.f * itemIdx),
		0, 16 ,16 };
	item->AddComponent(std::move(texture));

	auto col = std::make_unique<dae::ColliderComponent>(*item,
	 dae::ColliderComponent::ColliderInfo{
	     dae::ColliderComponent::ColliderType::Solid, false, { 48.f, 48.f }, {},
	     static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Item),
	     static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Player) | static_cast<uint32_t>(dae::ColliderComponent::ColliderTag::Level)
	 });
	item->AddComponent(std::move(col));


	// OBSERTVER


	item->SetLocalPosition({ pos.x + initialVelocity.x / 2,pos.y + initialVelocity.y / 2,pos.z });
	scene.Add(std::move(item));

	Level::TotalPickups++;
}
