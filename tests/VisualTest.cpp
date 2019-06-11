#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <filesystem>

using namespace std::string_literals;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <util/Types.hpp>
#include <util/Id.hpp>
#include <system/Vector2.hpp>
#include <system/Size.hpp>
#include <system/Color.hpp>
#include <ecs/Entity.hpp>
#include <ecs/System.hpp>
#include <graphics/Components.hpp>
#include <graphics/Render.hpp>
#include <graphics/Texture.hpp>
#include <graphics/DrawSystem.hpp>
#include <graphics/Window.hpp>

#include <iostream>

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    
    auto render{ std::make_shared<flm::Render>(
        std::make_unique<flm::Window>("game", flm::Vector2i{ 200, 200 }, flm::Size{ 720, 480 }),
        flm::Color{ 0, 0, 0, 255 }
    ) };

    auto transformComponent{ std::make_shared<flm::TransformComponent>() };
    {
        transformComponent->position = flm::Vector2f{ 100, 100 };
        transformComponent->rotation = 45;
        transformComponent->scale = flm::Vector2f{ 1.5, 1.5 };
    }

    auto textureComponent{ std::make_shared<flm::TextureComponent>() };
    {
        auto path{ argc > 1 ? argv[1] : "" };
        textureComponent->texture = std::make_shared<flm::Texture>(path + "picture.png"s, render);
    }

    const auto entity{ std::make_shared<flm::Entity>() };

    flm::DrawSystem system{ render };
    system.GetRoot()->AddChild(entity, 0);

    auto id1{ entity->AddComponent<flm::TransformComponent>(transformComponent) };
    auto id2{ entity->AddComponent<flm::TextureComponent>(textureComponent) };

    SDL_Event event;

    while (true) {
        float dt{ 0 };
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                exit(1);
            }
        }

        SDL_RenderClear(render->Get());
        system.Update(dt);
        SDL_RenderPresent(render->Get());
    }

    return 0;
}
