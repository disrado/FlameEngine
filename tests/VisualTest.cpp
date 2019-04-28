#include <memory>
#include <string>

using namespace std::string_literals;

#include <system/Color.hpp>
#include <system/Size.hpp>
#include <system/Vector2.hpp>
#include <graphics/Render.hpp>
#include <graphics/Window.hpp>

int main()
{
    auto window{ std::make_unique<flm::Window>(
        "game", flm::Vector2i{ 200, 200 }, flm::Size{ 1366, 768 }) };

    flm::Render render{ std::move(window), flm::Color{ 0, 0, 0, 255} };

    return 0;
}
