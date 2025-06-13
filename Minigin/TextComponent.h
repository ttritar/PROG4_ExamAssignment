#pragma once
#include <string>
#include <memory>

#include "GameObject.h"
#include "BaseComponent.h"
#include "Font.h"
#include "Texture2D.h"

namespace dae
{
	class Font;
	class Texture2D;

	class TextComponent final : public dae::BaseComponent
	{
	public:
		void Update(float deltaTime) override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetColor(const glm::vec4& color);
		glm::vec4 GetColor() const;

		TextComponent(dae::GameObject& owner, const std::string& text, dae::Font* font);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	private:
		bool m_needsUpdate;
		std::string m_text;
		dae::Font* m_font;
		SDL_Color m_color{ 255, 255, 255, 255};
		std::unique_ptr<dae::Texture2D> m_textTexture;
	};
}
