#pragma once

#include <cstdint>
#include <types/Types.hpp>

namespace flm::utils
{

class IdGenerator
{
public:
	template<typename T>
	static Id TypeId() noexcept
	{
		static Id newId{ 0 };
		return newId++;
	}
	
	static Id UniqueId() noexcept
	{
		static Id newId{ 0 };
		return newId++;
	}
};

}	// namespace flm::utils