#pragma once


#include <util/IdGenerator.hpp>

#include <iostream>


namespace flm
{


class Entity
{
public:
    template<typename T>
    Id AddComponent(std::shared_ptr<T> component);

    template<typename T>
    void RemoveComponent(const Id id);
    
    template<typename T>
    std::shared_ptr<T> GetComponent(const Id id) const;

private:
    Id m_id;
    std::map<Id, std::map<Id, std::shared_ptr<void>>> m_components;
};


template<typename T>
Id Entity::AddComponent(std::shared_ptr<T> component)
{
    const auto id{ IdGenerator::UniqueId() };
    const auto res{ m_components[IdGenerator::TypeId<T>()].insert({ id, component }) };

    if (!res.second) {
        throw std::runtime_error("Unable to add component to entity");
    }

    return id;
}


template<typename T>
void Entity::RemoveComponent(const Id id)
{
    m_components.at(IdGenerator::TypeId<T>()).erase(id);
}


template<typename T>
std::shared_ptr<T> Entity::GetComponent(const Id id) const
{
    for (auto group : m_components) {
        std::cout << "Group ID: " << group.first << std::endl;
        for (auto component : group.second) {
            std::cout << "Component id: " << component.first << std::endl;
        }
    }

    if (auto it{ m_components.find(IdGenerator::TypeId<T>()) }; it != std::end(m_components)) {
        std::cout << "Here1" << std::endl;
        if (auto component{ it->second.find(id) }; component != std::end(it->second)) {
            std::cout << "Here2" << std::endl;
            return std::static_pointer_cast<T>(component->second);
        }
    }

    return nullptr;
}


}	// flm