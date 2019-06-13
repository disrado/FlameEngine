#include "pch.hpp"

#include "ecs/Entity.hpp"

namespace flm
{

Id Entity::GetId() const
{
    return m_id;
}

} // namepsace flm