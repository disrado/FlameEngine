#include <memory>
#include <string>
#include <filesystem>

using namespace std::string_literals;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <system/Color.hpp>
#include <system/Size.hpp>
#include <system/Vector2.hpp>
#include <graphics/Render.hpp>
#include <graphics/Sprite.hpp>
#include <graphics/Texture.hpp>
#include <graphics/Window.hpp>

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    auto render{ std::make_shared<flm::Render>(
        std::make_unique<flm::Window>("game", flm::Vector2i{ 200, 200 }, flm::Size{ 720, 480 }),
        flm::Color{ 0, 0, 0, 255 }
    ) };

    flm::Sprite sprite{ std::make_shared<flm::Texture>("picture.jpg", render) };
    sprite.SetScale(flm::Vector2f{ 1.5, 1.5 });
    sprite.SetPosition(flm::Vector2f{ 100, 100 });
    sprite.SetRatation(45);

    SDL_Event event;

    while (true) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                exit(1);
            }
        }

        SDL_RenderClear(render->Get());
        sprite.Draw(render);
        SDL_RenderPresent(render->Get());

    }

    return 0;
}
