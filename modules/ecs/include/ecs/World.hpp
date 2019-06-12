#pragma once

#include <ecs/System.hpp>

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
    Id AddSystem(std::shared_ptr<System> system, uint64_t priority);

    bool RemoveSystem(Id id);

    bool SetPriority(Id id, uint64_t priority);

    void Update(float dt);

private:
    std::vector<QueueItem> m_systems;
};

} // namepsace flm