#include "pch.hpp"

#include "graphics/Render.hpp"

#include "graphics/Window.hpp"

namespace flm
{

Render::Render(std::unique_ptr<Window> window, Color color)
    : m_window{ std::move(window) }
    , m_render{ SDL_CreateRenderer(m_window->Get(), -1, SDL_RENDERER_ACCELERATED) }
{
    if (!m_render) {
        throw std::runtime_error("Cannot create window: "s + SDL_GetError());
    }

    SDL_SetRenderDrawColor(m_render, color.r, color.g, color.b, color.a);
}


Render::~Render()
{
    SDL_DestroyRenderer(m_render);
}


SDL_Renderer* Render::Get() const
{
    return m_render;
}

} // namepsace flm
