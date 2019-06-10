#pragma once

#include <util/Types.hpp>

namespace flm
{

class IdGen final
{
public:
	template<typename T>
	static Id TypeId() noexcept
	{
		static Id newId{ UniqueId() };


		return newId;
	}
	
	static Id UniqueId() noexcept
	{
		static Id newId{ 0 };
		return newId++;
	}
};

}	// namespace flm