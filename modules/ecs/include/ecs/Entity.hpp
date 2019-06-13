#pragma once

#include <memory>
#include <unordered_map>

#include <util/Id.hpp>
#include <util/Types.hpp>

namespace flm
{

class Entity final
{
public:
    // Adds component to entity
    template<typename T>
    bool AddComponent(std::shared_ptr<T> component);

    // Removes component from entity
    template<typename T>
    bool RemoveComponent();

    // Returns entity component if it is exist
    template<typename T>
    std::shared_ptr<T> GetComponent() const;

    // Returns id
    Id GetId() const;

private:
    const Id m_id = UniqueId();
    std::unordered_map<Id, std::shared_ptr<void>> m_components;
};

#include "../../src/Entity.inl"

} // namepsace flm