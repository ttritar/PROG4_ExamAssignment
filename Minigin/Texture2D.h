#pragma once
#include <vec2.hpp>
#include <string>
#include <SDL_rect.h>

struct SDL_Texture;
namespace dae
{
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2D final
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		explicit Texture2D(SDL_Texture* texture);
		explicit Texture2D(const std::string& fullPath);
		~Texture2D();

		glm::ivec2 GetSize() const;

		void SetSourceRect(const SDL_Rect& srcRect);
		const SDL_Rect* GetSourceRect() const;

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;
	private:
		SDL_Texture* m_texture;

		bool m_UseSourceRect{ false };
		SDL_Rect m_SourceRect;
	};
}
