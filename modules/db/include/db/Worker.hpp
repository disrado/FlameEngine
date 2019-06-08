#pragma once

#include "db/Types.hpp"
#include "db/Pool.hpp"


namespace flm::db
{


//
// Provides access to database
//
class Worker
{
	//
	// Construction and destruction.
	//
public:
	// connection - Shared pointer to RAII object which provides connection to database.
	Worker(ConnUnitShPtr connection);
	// connection - Unique pointer to RAII object which provides connection to database.
	Worker(ConnUnitUnPtr connection);
	// Virtual destructor.
	virtual ~Worker() = default;

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
	void Init(ConnUnitShPtr connection);

	//
	// Private data members.
	//
private:
	// RAII object which provides connection to database.
	ConnUnitShPtr m_connection;
	// Database api worker.
	WorkShPtr m_work;
};


}	// namespace flm::db