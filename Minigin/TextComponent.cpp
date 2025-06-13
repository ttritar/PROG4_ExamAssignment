#include "TextComponent.h"

#include <stdexcept>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Font.h"

dae::TextComponent::TextComponent(dae::GameObject& owner,const std::string& text, dae::Font* font)
	: BaseComponent (owner)
	,m_needsUpdate(true), m_text(text), m_font(font), m_textTexture(nullptr)
{
}

void dae::TextComponent::Update( float )
{

	if (m_needsUpdate)
	{
		const SDL_Color color = m_color;
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_textTexture = std::make_unique< dae::Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
	if (m_textTexture != nullptr)
	{
		const auto& pos = GetOwner()->GetWorldPosition();
		dae::Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}

void dae::TextComponent::SetColor(const glm::vec4& color)
{
	m_color = {
		static_cast<Uint8>(color.x * 255),
		static_cast<Uint8>(color.y * 255),
		static_cast<Uint8>(color.z * 255),
		static_cast<Uint8>(color.w * 255)
	};
	m_needsUpdate = true;
}

glm::vec4 dae::TextComponent::GetColor() const
{
	return glm::vec4{
		static_cast<float>(m_color.r) / 255.f,
		static_cast<float>(m_color.g) / 255.f,
		static_cast<float>(m_color.b) / 255.f,
		static_cast<float>(m_color.a) / 255.f
	};
}


