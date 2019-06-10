#pragma once

#include <util/Types.hpp>

#include <iostream>

namespace flm
{

class IdGenerator final
{
public:
	template<typename T>
	static Id TypeId() noexcept
	{
		static Id newId{ 0 };

		std::cout << "ID: " << newId << std::endl;

		return newId++;
	}
	
	static Id UniqueId() noexcept
	{
		static Id newId{ 0 };
		return newId++;
	}
};

}	// namespace flm