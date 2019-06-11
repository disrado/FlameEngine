#include "pch.hpp"

#include <util/Id.hpp>

namespace flm
{

Id UniqueId() noexcept
{
    static Id newId{ 0 };
    return newId++;
}

} // namepsace flm