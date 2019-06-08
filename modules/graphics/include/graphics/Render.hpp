#pragma once

class SDL_Renderer;

namespace flm
{

class Window;

class Render final
{
public:
	Render(std::unique_ptr<Window> window, Color color);
	~Render();

	SDL_Renderer* Get() const;


private:
	std::unique_ptr<Window> m_window;
	SDL_Renderer* m_render;
};

} // flm
