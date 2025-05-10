#pragma once
#include <memory>
#include <string>

#include "GameObject.h"

#include "BaseComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"


namespace cat
{
	class TextureComponent final : public dae::BaseComponent
	{
	public:

		void Update(float ) override
		{
		}

		void Render() const override
		{	
			const auto& pos = GetOwner()->GetWorldPosition();
			dae::Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
		}


		void SetSourceRect(SDL_Rect srcRect)
		{
			m_texture->SetSourceRect(srcRect);
		}

		SDL_Rect GetSourceRect() const
		{
			SDL_Rect src = GetSourceRect();
			return src;
		}


		// CTOR & DTOR
		//-------------
		TextureComponent(std::shared_ptr<dae::GameObject> owner,const std::string& filename)
			:BaseComponent(*owner)
		{
			m_texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
		};
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

	private:
		std::shared_ptr<dae::Texture2D> m_texture{};
	};
}
