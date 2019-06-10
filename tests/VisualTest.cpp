#include <map>
#include <memory>
#include <string>
#include <filesystem>

using namespace std::string_literals;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <util/Types.hpp>
#include <system/Vector2.hpp>
#include <system/Size.hpp>
#include <ecs/Components.hpp>
#include <ecs/Entity.hpp>
#include <system/Color.hpp>
#include <graphics/Render.hpp>
#include <graphics/Sprite.hpp>
#include <graphics/Texture.hpp>
#include <graphics/Window.hpp>

#include <iostream>

int main()
{
    auto transformComponent{ std::make_shared<flm::Transform>() };
    auto textureComponent{ std::make_shared<flm::Texture>() };

    flm::Entity entity;
    std::cout << "There 1" << std::endl;
    auto id1{ entity.AddComponent<flm::Transform>(transformComponent) };
    std::cout << "There 2" << std::endl;
    auto id2{ entity.AddComponent<flm::Texture>(textureComponent) };

    auto ptr{ entity.GetComponent<flm::Transform>(id1) };


    if (ptr) {
        std::cout << ptr->m_rotation << std::endl;
    } else {
        std::cout << "There is nothing to do" << std::endl;
    }




    // SDL_Init(SDL_INIT_EVERYTHING);

    // auto render{ std::make_shared<flm::Render>(
    //     std::make_unique<flm::Window>("game", flm::Vector2i{ 200, 200 }, flm::Size{ 720, 480 }),
    //     flm::Color{ 0, 0, 0, 255 }
    // ) };

    // flm::Sprite sprite{ std::make_shared<flm::Texture>("picture.jpg", render) };
    // sprite.SetScale(flm::Vector2f{ 1.5, 1.5 });
    // sprite.SetPosition(flm::Vector2f{ 100, 100 });
    // sprite.SetRatation(45);

    // SDL_Event event;

    // while (true) {
    //     if (SDL_PollEvent(&event)) {
    //         if (event.type == SDL_KEYDOWN) {
    //             exit(1);
    //         }
    //     }

    //     SDL_RenderClear(render->Get());
    //     sprite.Draw(render);
    //     SDL_RenderPresent(render->Get());

    // }

    return 0;
}
