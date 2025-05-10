#include "Level.h"
#include "../3rdParty/json/tileson.hpp"
#include <fstream>

#include "ColliderComponent.h"
#include "CollisionSystem.h"
#include "Texture2D.h"
#include "TextureComponent.h"
#include "Transform.h"

cat::Level::Level(dae::Scene& scene)
	:m_Scene(scene)
{
}

void cat::Level::LoadLevel(int idx)
{
	// LOAD
	//----------
	tson::Tileson parser;
	std::unique_ptr<tson::Map> map = parser.parse(m_LevelPaths[idx]);

	if (map->getStatus() != tson::ParseStatus::OK) {
		std::cerr << "Failed to load map: " << map->getStatusMessage() << std::endl;
		return;
	}

	const auto& tilesets = map->getTilesets();
	if (tilesets.empty())
	{
		std::cerr << "No tilesets found!" << std::endl;
		return;
	}

	// DRAW AND MAKE EVERYTHING
	//--------------------------
	for (auto& layer : map->getLayers())
	{
		if (layer.getType() != tson::LayerType::TileLayer)
			continue;

		for (int y = 0; y < layer.getSize().y; ++y)
		{
			for (int x = 0; x < layer.getSize().x; ++x)
			{
				tson::Tile* tile = layer.getTileData(x, y);
				if (!tile) continue;

				int gid = tile->getGid();
				if (gid == 0) continue;

				// Determine which tileset the gid corresponds to
				const tson::Tileset* activeTileset = nullptr;
				for (const auto& tileset : tilesets) {
					if (gid >= tileset.getFirstgid() && gid < (tileset.getFirstgid() + tileset.getTileCount())) {
						activeTileset = &tileset;
						break;
					}
				}

				if (!activeTileset) {
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

				// Create the tile GameObject
				std::shared_ptr<dae::GameObject> tileObj = std::make_shared<dae::GameObject>();
				tileObj->SetLocalPosition(glm::vec3(x * tileWidth, y * tileHeight, 0));

				// texture component
				std::string tilesetImagePath = "../Data/Levels/" + std::to_string(idx) + "/" + activeTileset->getImagePath().string();
				auto tex = std::make_shared<TextureComponent>(tileObj, tilesetImagePath);
				tex->SetSourceRect(srcRect);
				tileObj->AddComponent(tex);

				// collider component
				ColliderComponent::ColliderInfo colliderInfo{};
				//if (tile->getProp("type"))
				colliderInfo.type = ColliderComponent::ColliderType::TopOnly;
				colliderInfo.isStatic = true;
				colliderInfo.size = { tileWidth, tileHeight };

				auto col = std::make_shared<ColliderComponent>(tileObj, colliderInfo);
				tileObj->AddComponent(col);
				CollisionSystem::GetInstance().AddCollider(col.get());

				m_Scene.Add(tileObj);
			}
		}
	}
}


void cat::Level::AddLevel(const std::string& filePath)
{
	m_LevelPaths.emplace_back(filePath);
}

