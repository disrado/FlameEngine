#pragma once

namespace flm
{

class Render;
class Texture;

class Sprite
{
public:
	Sprite(std::shared_ptr<Texture> texture);
	
	const Vector2f& GetPosition() const;
	const Vector2f& GetScale() const;
	float GetRatation() const;

	void SetPosition(const Vector2f& position);
	void SetScale(const Vector2f& scale);
	void SetRatation(const float rotation);

	void Draw(std::shared_ptr<Render> render) const;

private:
	std::shared_ptr<Texture> m_texture = nullptr;
	Size m_realSize = { 0, 0 };
	Vector2f m_position = { 0, 0 };
	Vector2f m_scale = { 1, 1 };
	float m_rotation = 0;
};

} // flm
