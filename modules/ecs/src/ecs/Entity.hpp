#pragma once


#include "ecs/Component.hpp"

#include <types/Types.hpp>

#include <vector>


namespace flm::ecs
{


class Entity
{
public:
	void AddComponent(std::shared_ptr<Component> newComponent);
	void RemoveComponent(std::shared_ptr<Component> component);
	std::shared_ptr<Component> GetComponent(Id id) const;

private:
	Id m_id;
	std::vector<std::shared_ptr<Component>> m_components;
};


}	// flm::ecs