#include "TextureComponent.h"

void cat::TextureComponent::Update(float )
{
	m_DestSize = {
		static_cast<int>(m_pTexture->GetSourceRect()->w * g_SCALE),
		static_cast<int>(m_pTexture->GetSourceRect()->h * g_SCALE)
	};
}

void cat::TextureComponent::Render() const
{
	const auto& pos = GetOwner()->GetWorldPosition();
	dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y, m_DestSize.x, m_DestSize.y, FlipFlag);
}

cat::TextureComponent::TextureComponent(std::shared_ptr<dae::GameObject> owner, const std::string& filename)
	:BaseComponent(*owner)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
	SetSourceRect({
		0, 0,
		m_pTexture->GetSize().x,
		m_pTexture->GetSize().y
		});
};
