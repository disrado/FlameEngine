#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include <unordered_map>

#include <util/Id.hpp>
#include <util/Types.hpp>

#include <ecs/System.hpp>
#include <ecs/Entity.hpp>

namespace flm
{

class World final
{
private:
    class QueueItem
    {
    public:
        QueueItem(std::shared_ptr<System> system, uint64_t handlePriority);

        bool operator<(const QueueItem& other) { return priority < other.priority; }

    public:
        std::shared_ptr<System> system;
        uint64_t priority;
        Id id;
    };

public:
    // Adds system to world systems pool
    Id AddSystem(std::shared_ptr<System> system, uint64_t priority);

    // Removes system from world
    bool RemoveSystem(Id id);

    // Sets system update prioiry
    bool SetPriority(Id id, uint64_t priority);

    // Creates entity
    std::shared_ptr<Entity> CreateEntity();

    // Returns entity by id
    std::shared_ptr<Entity> GetEntity(Id id) const;

    // Removes entity from world
    bool RemoveEntity(Id id);

    // Update all systems
    void Update(float dt);

private:
    std::vector<QueueItem> m_systems;
    std::unordered_map<Id, std::shared_ptr<Entity>> m_entities;
};

} // namepsace flm