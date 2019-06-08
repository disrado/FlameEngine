#pragma once

namespace flm::db
{

using Handle = pqxx::lazyconnection;
using HandleShPtr = std::shared_ptr<Handle>;
using WorkShPtr = std::shared_ptr<pqxx::work>;
using Result = pqxx::result;

}	// namespace flm::db