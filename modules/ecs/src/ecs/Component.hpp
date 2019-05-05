#pragma once

#include <types/Types.hpp>

#include <memory>


namespace flm::ecs
{


class Component
{
public:
	template<typename T>
	Component();

	virtual ~Component();

	Component(const Component&) = default;
	Component& operator=(const Component&) = default;
	Component(Component&&) = default;
	Component& operator=(Component&&) = default;


	Id GetId() const;

private:
	const Id m_id;
};

// using ComponentUPtr = std::unique_ptr<Component>;
// using ComponentSPtr = std::shared_ptr<Component>


}	// namepsace flm::ecs