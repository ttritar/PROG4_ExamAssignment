#pragma once
#include <memory>
#include <string>

#include "GameObject.h"

#include "BaseComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"


namespace dae
{
	static float g_SCALE{ 3.f };

	class TextureComponent final : public dae::BaseComponent
	{
	public:

		void Update(float) override;
		void Render() const override;

		void SetSourceRect(SDL_Rect srcRect)
		{
			m_pTexture->SetSourceRect(srcRect);
		}
		SDL_Rect GetSourceRect() const
		{
			return *m_pTexture->GetSourceRect();
		}


		// CTOR & DTOR
		//-------------
		TextureComponent(dae::GameObject& owner, const std::string& filename);
		virtual ~TextureComponent() = default;

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		// Members
		//-------------
		SDL_RendererFlip FlipFlag = SDL_FLIP_NONE;

	private:
		dae::Texture2D* m_pTexture{};
		glm::vec2 m_DestSize{};
	};
}
