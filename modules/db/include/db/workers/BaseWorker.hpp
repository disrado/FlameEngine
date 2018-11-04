#pragma once

#include "db/Types.hpp"
#include "db/ConnectionPool.hpp"


namespace flm::db
{


class BaseWork
{
public:
	BaseWork(ConnectionUnitShPtr connection);
	virtual ~BaseWork() = default;

protected:
	Result Exec(const std::string& query) const;
	void Commit() const;
	std::string Esc(const std::string& str) const;
	
private:
	ConnectionUnitShPtr m_connection;
	WorkShPtr m_work;
};


}	// namespace flm::db