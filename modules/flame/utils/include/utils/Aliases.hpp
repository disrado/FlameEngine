#pragma once

namespace flm::utils
{


template<typename T>
using ShPtr = std::shared_ptr<T>;

template<typename T>
using UnPtr = std::unique_ptr<T>;

template<typename T>
using WkPtr = std::weak_ptr<T>;

template<typename T>
using func = std::function<T>;

using Seconds = std::chrono::seconds;


} // namespace flm::db