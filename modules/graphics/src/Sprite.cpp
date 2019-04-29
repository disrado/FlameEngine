#include "pch.hpp"

#include "graphics/Sprite.hpp"
#include "graphics/Render.hpp"
#include "graphics/Texture.hpp"

namespace flm
{

Sprite::Sprite(std::shared_ptr<Texture> texture)
	: m_texture{ texture }
{}


const Vector2f& Sprite::GetPosition() const {
	return m_position;
}


const Vector2f& Sprite::GetScale() const {
	return m_scale;
}


float Sprite::GetRatation() const {
	return m_rotation;
}


void Sprite::SetPosition(const Vector2f& position) {
	m_position = position;
}


void Sprite::SetScale(const Vector2f& scale) {
	m_scale = scale;
}


void Sprite::SetRatation(const float rotation) {
	m_rotation = rotation;
}


void Sprite::Draw(std::shared_ptr<Render> render) const
{
	SDL_Rect rect;
	rect.w = m_texture->GetSize().width * m_scale.x;
	rect.h = m_texture->GetSize().height * m_scale.y;
	rect.x = m_position.x;
	rect.y = m_position.y;

	SDL_RenderCopyEx(
		render->Get(), m_texture->Get(), nullptr, &rect, m_rotation, nullptr, SDL_FLIP_NONE);
}

} // flm
