#pragma once

#include <util/Types.hpp>

namespace flm
{

Id UniqueId() noexcept;

template<typename T>
Id TypeId() noexcept
{
    static Id newId{ UniqueId() };
    return newId;
}

} // namespace flm