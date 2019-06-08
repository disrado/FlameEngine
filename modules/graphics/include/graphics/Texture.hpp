#pragma once

struct SDL_Texture;

namespace flm
{

class Render;

class Texture
{
public:
	Texture(std::filesystem::path path, std::shared_ptr<Render> render);
	
	Size GetSize() const;
	SDL_Texture* Get() const;

private:
	SDL_Texture* m_texture = nullptr;
	Size m_size = { 0, 0 };
};

} // flm
