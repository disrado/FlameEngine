#include "pch.hpp"

#include "ecs/Entity.hpp"

namespace flm
{

bool Entity::RemoveComponent(const Id id)
{
    if (m_components.erase(id)) {
        auto it{ std::find_if(std::begin(m_componentTypes), std::end(m_componentTypes),
            [id] (auto item) { return item.second == id; }
        ) };

        if (m_componentTypes.erase(it->first) == 0) {
            throw std::runtime_error("Entity corrupted");
        }

        return true;
    }

    return false;
}

} // namepsace flm