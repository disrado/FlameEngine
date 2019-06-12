#include "pch.hpp"

#include "ecs/World.hpp"

namespace flm
{

World::QueueItem::QueueItem(std::shared_ptr<System> system, uint64_t handlePriority)
    : system{ std::move(system) }
    , priority{ handlePriority }
    , id{ UniqueId() }
{
}

Id World::AddSystem(std::shared_ptr<System> system, uint64_t priority)
{
    const auto& newItem{ m_systems.emplace_back(system, priority) };
    std::sort(std::begin(m_systems), std::end(m_systems));

    return newItem.id;
}


bool World::RemoveSystem(Id id)
{
    const auto it{ std::find_if(std::begin(m_systems), std::end(m_systems),
        [id] (const auto& item) { return item.id == id; })
    };

    if (it != std::end(m_systems)) {
        m_systems.erase(it);
        return true;
    }

    return false;
}


bool World::SetPriority(Id id, uint64_t priority)
{
    const auto it{ std::find_if(std::begin(m_systems), std::end(m_systems),
        [id] (const auto& item) { return item.id == id; })
    };

    if (it != std::end(m_systems)) {
        it->priority = priority;
        std::sort(std::begin(m_systems), std::end(m_systems));
        return true;
    }

    return false;
}


void World::Update(float dt)
{
    for(auto item : m_systems) {
        item.system->Update(dt);
    }
}

} // namepsace flm