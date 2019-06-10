#pragma once

namespace flm
{


class Entity
{
public:
    template<typename T>
    Id AddComponent(std::shared_ptr<T> component);

    template<typename T>
    bool RemoveComponent();

    bool RemoveComponent(const Id id);

    template<typename T>
    std::shared_ptr<T> GetComponent() const;

    template<typename T>
    std::shared_ptr<T> GetComponent(const Id id) const;

public:
    const Id m_id = IdGen::UniqueId();

private:
    std::map<Id, std::shared_ptr<void>> m_components;
    std::map<Id, Id> m_componentTypes;
};


template<typename T>
Id Entity::AddComponent(std::shared_ptr<T> component)
{
    const auto id{ IdGen::UniqueId() };

    m_components.insert({ id, component });
    m_componentTypes[IdGen::TypeId<T>()] = id;

    return id;
}


template<typename T>
bool Entity::RemoveComponent()
{
    const auto typeId{ IdGen::TypeId<T>() };

    if (m_componentTypes.count(typeId)) {
        if (m_components.erase(m_componentTypes[typeId]) + m_componentTypes.erase(typeId)) {
            return true;
        }
        
        throw std::runtime_error("Entity corrupted");
    }

    return false;
}


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


template<typename T>
std::shared_ptr<T> Entity::GetComponent() const
{
    const auto typeId{ IdGen::TypeId<T>() };

    if (m_componentTypes.count(typeId)) {
        return std::static_pointer_cast<T>(m_components.at(m_componentTypes[typeId]));
    }

    return nullptr;
}


template<typename T>
std::shared_ptr<T> Entity::GetComponent(const Id id) const
{
    if (m_components.count(id)) {
        return std::static_pointer_cast<T>(m_components.at(id));
    }

    return nullptr;
}


}	// flm