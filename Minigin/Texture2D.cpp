#include <SDL.h>
#include <SDL_image.h>
#include "Texture2D.h"
#include "Renderer.h"
#include <stdexcept>

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_texture);
}

glm::ivec2 dae::Texture2D::GetSize() const
{
	SDL_Rect dst;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

void dae::Texture2D::SetSourceRect(const SDL_Rect& srcRect)
{
	m_SourceRect = srcRect;
	m_UseSourceRect = true;
}

const SDL_Rect* dae::Texture2D::GetSourceRect() const
{
	if (m_UseSourceRect) return &m_SourceRect;
	return nullptr;
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_texture;
}

dae::Texture2D::Texture2D(const std::string &fullPath)
{
	m_texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (m_texture == nullptr)
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
}

dae::Texture2D::Texture2D(SDL_Texture* texture)	: m_texture{ texture } 
{
	assert(m_texture != nullptr);
}

