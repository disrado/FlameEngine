#include "ecs/Component.hpp"

#include <utils/IdGenerator.hpp>

namespace flm::ecs
{


template<typename T>
Component::Component() : m_id{ utils::IdGenerator::TypeId<Component>() }
{}


Component::~Component() = default;


Id Component::GetId() const
{
	return m_id;
}

}	// namepsace flm::ecs