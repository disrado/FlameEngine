#pragma once

namespace flm
{


struct Transform
{
    Vector2f m_position = { 0, 0 };
    Vector2f m_scale = { 1, 1 };
    float m_rotation = 0;
};


struct Texture
{
    SDL_Texture* m_texture = nullptr;
    Size m_size = { 0, 0 };
};


} // namepsace flm