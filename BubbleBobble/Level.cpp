#include "Level.h"
#include "../3rdParty/json/tileson.hpp"

#include "ColliderComponent.h"
#include "TextureComponent.h"
#include "TextComponent.h"

#include "Presets.h"

#include "ServiceLocator.h"

cat::Level::Level(dae::Scene& scene, int levelNr, const std::string& filePath)
	:m_Scene(scene), m_LevelPath(filePath)
{
	auto fontUI = dae::ResourceManager::GetInstance().LoadFont("font.ttf", 20);

	auto level = std::make_unique<dae::GameObject>();
	level->SetLocalPosition({ 360,50,0 });
	auto textLevel = std::make_unique<cat::TextComponent>(*level, std::format("{:02}", levelNr), fontUI);
	level->AddComponent(std::move(textLevel));
	m_Scene.Add(std::move(level));

	LoadLevel();
}

void cat::Level::LoadLevel()
{
	const dae::sound_id soundId = static_cast<dae::sound_id>(dae::make_sdbm_hash("MainTheme"));
	dae::ServiceLocator::GetInstance().GetSoundSystem().LoadSound(soundId, "../Data/Levels/MainTheme.mp3");
	dae::ServiceLocator::GetInstance().GetSoundSystem().Play(soundId, 100);

	// LOAD
	//----------
	tson::Tileson parser;
	std::unique_ptr<tson::Map> map = parser.parse(m_LevelPath);

	if (map->getStatus() != tson::ParseStatus::OK) {
		std::cerr << "Failed to load map: " << map->getStatusMessage() << std::endl;
		return;
	}

	auto& tilesets = map->getTilesets();
	if (tilesets.empty())
	{
		std::cerr << "No tilesets found!" << std::endl;
		return;
	}


	// DRAW AND MAKE EVERYTHING
	//--------------------------
	for (auto& layer : map->getLayers())
	{
		switch (layer.getType())
		{

			// TILES
			case tson::LayerType::TileLayer:
		{
			for (int y = 0; y < layer.getSize().y; ++y)
			{
				for (int x = 0; x < layer.getSize().x; ++x)
				{
					tson::Tile* tile = layer.getTileData(x, y);
					if (!tile) continue;

					int gid = tile->getGid();
					if (gid == 0) continue;

					// Determine which tileset the gid corresponds to
					tson::Tileset* activeTileset = nullptr;
					for (auto& tileset : tilesets)
					{
						if (gid >= tileset.getFirstgid() && gid < (tileset.getFirstgid() + tileset.getTileCount()))
						{
							activeTileset = &tileset;
							break;
						}
					}

					if (!activeTileset)
					{
						std::cerr << "Failed to find a matching tileset for gid: " << gid << std::endl;
						continue;
					}

					// Calculate the local ID and source rectangle for the tile
					int localId = gid - activeTileset->getFirstgid();
					int tileWidth = activeTileset->getTileSize().x;
					int tileHeight = activeTileset->getTileSize().y;
					int columns = activeTileset->getColumns();

					int srcX = (localId % columns) * tileWidth;
					int srcY = (localId / columns) * tileHeight;
					SDL_Rect srcRect{ srcX, srcY, tileWidth, tileHeight };


					// PROPERTIES
					//----------------
					int collisionType = -1;

					auto colProp = tile->getProp("col");
					if (colProp)
					{
						collisionType = colProp->getValue<int>();
					}
					else
					{
						// If not found in layer tile, check the tileset's tile definition
						tson::Tile* tilesetTile = activeTileset->getTile(localId);
						if (tilesetTile)
						{
							auto tilesetColProp = tilesetTile->getProp("col");
							if (tilesetColProp)
							{
								collisionType = tilesetColProp->getValue<int>();
							}
						}
					}



					// CREATE TILE GAMEOBJECT
					//--------------------------
					std::unique_ptr<dae::GameObject> tileObj = std::make_unique<dae::GameObject>();
					tileObj->SetLocalPosition(glm::vec3(x * tileWidth * g_SCALE, y * tileHeight * g_SCALE, 0));

					// texture component
					std::string tilesetImagePath = "../Data/Levels/" + activeTileset->getImagePath().string();
					auto tex = std::make_unique<TextureComponent>(*tileObj, tilesetImagePath);
					//tex->SetSourceRect(srcRect);
					tileObj->AddComponent(std::move(tex));

					// collider component
					dae::ColliderComponent::ColliderInfo colliderInfo{};
					if (collisionType != -1)
					{
						switch (collisionType)
						{
						case 0: // Solid
							colliderInfo.type = dae::ColliderComponent::ColliderType::Solid;
							break;
						case 1: // TopOnly
							colliderInfo.type = dae::ColliderComponent::ColliderType::TopOnly;
							break;
						default:;
						}
						colliderInfo.isStatic = true;
						colliderInfo.size = { tileWidth * g_SCALE, tileHeight * g_SCALE };

						auto col = std::make_unique<dae::ColliderComponent>(*tileObj, colliderInfo);
						tileObj->AddComponent(std::move(col));
					}


					m_Scene.Add(std::move(tileObj));
				}
			}
		}
			break;

			// OBJECTS
			case tson::LayerType::ObjectGroup:
			{
				bool spawn = true;
				for (auto& object : layer.getObjects())
				{
					if (object.getName() == "player" && spawn)
					{
						spawn = false; // only spawn one player
						glm::vec3 pos{ object.getPosition().x * g_SCALE, object.getPosition().y * g_SCALE, 0 };
						PlayerPreset player = { object.getProp("isPlayerOne")->getValue<bool>() };
						player.SpawnPlayer(m_Scene, pos);
					}
				}
				break;

			}

		}

	}
}

