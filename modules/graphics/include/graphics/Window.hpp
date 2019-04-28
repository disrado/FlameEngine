#pragma once

class SDL_Window;

namespace flm
{

class Window final
{
public:
	Window(std::string title, Vector2i position, Size size);
	~Window();

	SDL_Window* Get() const;
	Vector2i GetPosition() const;
	Size GetSize() const;

private:
	SDL_Window* m_window;
	Vector2i m_position;
	Size m_size;
};

} // flm
