template<typename T>
Id Entity::AddComponent(std::shared_ptr<T> component)
{
    const auto id{ UniqueId() };

    m_components.insert({ id, component });

    const auto typeId{ TypeId<T>()  };

    m_componentTypes[typeId] = id;

    return id;
}


template<typename T>
bool Entity::RemoveComponent()
{
    const auto typeId{ TypeId<T>() };

    if (m_componentTypes.count(typeId)) {
        if (m_components.erase(m_componentTypes[typeId]) + m_componentTypes.erase(typeId)) {
            return true;
        }
        
        throw std::runtime_error("Entity corrupted");
    }

    return false;
}


template<typename T>
std::shared_ptr<T> Entity::GetComponent() const
{
    const auto typeId{ TypeId<T>() };

    if (m_componentTypes.count(typeId)) {
        return GetComponent<T>(m_componentTypes.at(typeId));
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