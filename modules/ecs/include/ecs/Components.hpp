#pragma once

namespace flm
{


struct Transform
{
    Vector2f position = { 0, 0 };
    Vector2f scale = { 1, 1 };
    float rotation = 0;
};


struct Texture
{
    SDL_Texture* texture = nullptr;
    Size size = { 0, 0 };
};


} // namepsace flm