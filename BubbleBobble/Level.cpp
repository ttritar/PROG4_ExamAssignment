#include "Level.h"
#include "../3rdParty/json/tileson.hpp"
#include <fstream>

#include "ColliderComponent.h"
#include "CollisionSystem.h"
#include "Texture2D.h"
#include "TextureComponent.h"
#include "Transform.h"

namespace dae
{
	Level::Level(Scene& scene)
		:m_Scene(scene)
	{
	}

	void Level::LoadLevel(int idx)
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

        const auto& tileset = tilesets.front();
        std::string tilesetImagePath = "../Data/Levels/" + std::to_string(idx) + "/" + tileset.getImagePath().string();
        int tileWidth = tileset.getTileSize().x;
        int tileHeight = tileset.getTileSize().y;

        int columns = tileset.getColumns();


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

                    int localId = gid - tileset.getFirstgid();
                    int srcX = (localId % columns) * tileWidth;
                    int srcY = (localId / columns) * tileHeight;

                    SDL_Rect srcRect{ srcX, srcY, tileWidth, tileHeight };

                    std::shared_ptr<GameObject> tileObj = std::make_shared<GameObject>();
                    tileObj->SetLocalPosition(glm::vec3(x * tileWidth, y * tileHeight, 0));

                    // texture component
                    auto tex = std::make_shared<TextureComponent>(tileObj, tilesetImagePath);
                    tex->SetSourceRect(srcRect); 
                    tileObj->AddComponent(tex);

                    // collider component
					ColliderComponent::ColliderInfo colliderInfo{
						true, {tileWidth,tileHeight}
					};
                    auto col = std::make_shared<ColliderComponent>(tileObj,colliderInfo);
                    tileObj->AddComponent(col);
					CollisionSystem::GetInstance().AddCollider(col.get());


                    m_Scene.Add(tileObj);
                }
            }
        }

	}

	void Level::AddLevel(const std::string& filePath)
	{
        m_LevelPaths.emplace_back(filePath);
	}
}
