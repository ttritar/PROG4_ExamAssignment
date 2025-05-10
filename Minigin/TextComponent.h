#pragma once
#include <string>
#include <memory>

#include "GameObject.h"
#include "BaseComponent.h"
#include "Font.h"
#include "Texture2D.h"

namespace cat
{
	class Font;
	class Texture2D;

	class TextComponent final : public dae::BaseComponent
	{
	public:
		void Update(float deltaTime) override;
		void Render() const override;

		void SetText(const std::string& text);

		TextComponent(std::shared_ptr<dae::GameObject> owner, const std::string& text, std::shared_ptr<dae::Font> font);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	private:
		bool m_needsUpdate;
		std::string m_text;
		std::shared_ptr<dae::Font> m_font;
		std::shared_ptr<dae::Texture2D> m_textTexture;
	};
}
