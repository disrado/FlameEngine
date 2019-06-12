#pragma once

#include <unordered_map>

#include <util/Id.hpp>
#include <util/Types.hpp>

namespace flm
{

class Entity final
{
public:
    template<typename T>
    Id AddComponent(std::shared_ptr<T> component);

    template<typename T>
    bool RemoveComponent();

    template<typename T>
    std::shared_ptr<T> GetComponent() const;

public:
    const Id id = UniqueId();

private:
    std::unordered_map<Id, std::shared_ptr<void>> m_components;
};

#include "../../src/Entity.inl"

} // namepsace flm