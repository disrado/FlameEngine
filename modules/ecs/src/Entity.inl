template<typename T>
bool Entity::AddComponent(std::shared_ptr<T> component)
{
    return m_components.emplace(TypeId<T>(), component).second;
}


template<typename T>
bool Entity::RemoveComponent()
{
    return m_components.erase(TypeId<T>);
}


template<typename T>
std::shared_ptr<T> Entity::GetComponent() const
{
    if (auto it{ m_components.find(TypeId<T>()) }; it != std::end(m_components)) {
        return std::static_pointer_cast<T>(it->second);
    }

    return nullptr;
}
