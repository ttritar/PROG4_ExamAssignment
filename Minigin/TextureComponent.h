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
	static float g_BASE_SCALE =  3.f;

	class TextureComponent final : public dae::BaseComponent
	{
	public:

		void Update(float) override;
		void Render() const override;


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

		float Scale{ g_BASE_SCALE };

		SDL_Rect SrcRect{ 0, 0, 0, 0 };
	private:
		dae::Texture2D* m_pTexture{};
		glm::vec2 m_DestSize{};
	};
}
