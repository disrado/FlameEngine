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
    const Id id = UniqueId();

private:
    std::map<Id, std::shared_ptr<void>> m_components;
    std::map<Id, Id> m_componentTypes;
};

#include "../../src/Entity.inl"

} // namepsace flm