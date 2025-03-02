#pragma once
#include <memory>
#include <string>

#include "GameObject.h"

#include "BaseComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"



namespace dae 
{
	class TextureComponent final : public BaseComponent
	{
	public:

		void Update(float ) override
		{
		}

		void Render() const override
		{	
			const auto& pos = GetOwner()->GetWorldPosition();
			Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
		}



		TextureComponent(std::shared_ptr<dae::GameObject> owner,const std::string& filename)
			:BaseComponent(*owner)
		{
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
