#pragma once
#include "Scene.h"

#include "BubbleComponent.h"
#include "ColliderComponent.h"
#include "TextureComponent.h"

namespace cat
{
	// PLAYER
	//----------------
	struct PlayerPreset 
	{
		bool isPlayerOne;

		void SpawnPlayer(dae::Scene& scene, const glm::vec3 pos) const;
	};

	struct PLayerMaitaPreset
	{
		bool isPlayerOne;
		void SpawnPlayer(dae::Scene& scene, const glm::vec3 pos) const;
	};


	// BUBBLE
	//----------------
	struct BubblePreset
	{
		bool isPlayerOne;
		glm::vec2 direction;
		BubbleComponent::TrappedEnemyType type = BubbleComponent::TrappedEnemyType::None;

		void SpawnBubble(dae::Scene& scene, const glm::vec3 pos) const;
	};

	struct BoulderPreset
	{
		glm::vec2 direction;
		void SpawnBoulder(dae::Scene& scene, const glm::vec3 pos) const;
	};


	// ZEN-CHAN
	//----------------
	struct ZenChanPreset
	{
		static void SpawnZenChan(dae::Scene& scene, const glm::vec3 pos);
	};


	// ITEM
	//----------------
	struct ItemPreset
	{
		static void SpawnItem(dae::Scene& scene, const glm::vec3 pos);
	};
}
