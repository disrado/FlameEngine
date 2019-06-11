#include "pch.hpp"

#include "graphics/Window.hpp"

namespace flm
{

Window::Window(std::string title, Vector2i position, Size size)
    : m_window{ SDL_CreateWindow(
        title.c_str(),
        position.x,
        position.y,
        size.width,
        size.height,
        6 // SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    ) }
{
    if (!m_window) {
        throw std::runtime_error("Cannot create window: "s + SDL_GetError());
    }
}


Window::~Window()
{
    SDL_DestroyWindow(m_window);
}


SDL_Window* Window::Get() const
{
    return m_window;
}


Vector2i Window::GetPosition() const
{
    return m_position;
}


Size Window::GetSize() const
{
    return m_size;
}

} // namepsace flm
