#pragma once
#include <memory>
#include <string>

#include "BaseComponent.h"

#include "Transform.h"
#include "Renderer.h"
#include "ResourceManager.h"



namespace dae 
{
	class TextureComponent final : public BaseComponent
	{
	public:

		void Update(float deltaTime) override
		{
			deltaTime;
		}

		void Render() const override
		{
			const auto& pos = m_transform.GetPosition();
			Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
		}



		TextureComponent(const std::string& filename) {

			m_texture = ResourceManager::GetInstance().LoadTexture(filename);
		};
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

	private:
		std::shared_ptr<Texture2D> m_texture{};
	};
}
