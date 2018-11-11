#pragma once

#include "db/Types.hpp"
#include "db/ConnectionPool.hpp"


namespace flm::db
{


//
// Provides access to database
//
class BaseWork
{
	//
	// Construction and destruction.
	//
public:
	// connection - Shared pointer to RAII object which provides connection to database.
	BaseWork(ConnectionUnitShPtr connection);
	// connection - Unique pointer to RAII object which provides connection to database.
	BaseWork(ConnectionUnitUnPtr connection);
	// Virtual destructor.
	virtual ~BaseWork() = default;

	//
	// Protected interface.
	//
protected:
	// Executes sql query.
	Result Execute(const std::string& query) const;
	// Commits the database transaction.
	void Commit() const;
	// Transforms string literal to sql literal.
	std::string Esc(const std::string& str) const;
	
	//
	// Private methods.
	//
private:
	// connection - RAII object which provides connection to database.
	void Init(ConnectionUnitShPtr connection);

	//
	// Private data members.
	//
private:
	// RAII object which provides connection to database.
	ConnectionUnitShPtr m_connection;
	// Database api worker.
	WorkShPtr m_work;
};


}	// namespace flm::db