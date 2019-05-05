#include "ecs/Entity.hpp"

namespace flm::ecs
{


void Entity::AddComponent(std::shared_ptr<Component> newComponent)
{
	m_components.push_back(newComponent);
}


void Entity::RemoveComponent(std::shared_ptr<Component> component)
{
	std::remove(std::begin(m_components), std::end(m_components), component);
}


std::shared_ptr<Component> Entity::GetComponent(Id id) const
{
	const auto result{ std::find_if(std::begin(m_components), std::end(m_components),
		[id] (Id itemId) { return itemId == id; } )
	};

	if (result != std::end(m_components)) {
		return *result;
	}

	return nullptr;
}


} // flm::ecs