#pragma once

#include "db/Types.hpp"


namespace flm::db
{


class Connection;
using ConnectionShPtr = std::shared_ptr<Connection>;


class ConnectionUnit;
using ConnectionUnitShPtr = std::shared_ptr<ConnectionUnit>;
using ConnectionUnitUnPtr = std::unique_ptr<ConnectionUnit>;


//
// Holder for database connection.
//
class Connection
{
	//
	// Constraction and destruction.
	//
public:
	// config - config for database connection.
	explicit Connection(const std::string& config);

	//
	// Public interface.
	//
public:
	// Returns raw database connection handle.
	HandleShPtr GetHandle() const;

	//
	// Private data members.
	//
private:
	// Raw database connection handle.
	HandleShPtr m_handle;
};


//
// Class for supporting RAII with database connections.
//
class ConnectionUnit
{
	//
	// Public types.
	//
public:
	using ExpireCallback = std::function<void()>;

	//
	// Constraction and destruction.
	//
public:
	// connection - database connection.
	// callback - function which will be called when object will be destructing.
	ConnectionUnit(ConnectionShPtr connection, ExpireCallback callback);
	// Calls callback function.
	~ConnectionUnit();

	// Move construction is allowed.
	ConnectionUnit(ConnectionUnit&&) = default;
	// Move assignment is allowed.
	ConnectionUnit& operator=(ConnectionUnit&&) = default;

	// Copying is not allowed.
	ConnectionUnit(const ConnectionUnit&) = delete;
	// Copy assignment is not allowed.
	ConnectionUnit& operator=(const ConnectionUnit&) = delete;

	//
	// Public interface.
	//
public:
	// Returns raw database connection.
	ConnectionShPtr GetConnection() const;

	//
	// Private data members.
	//
private:
	// Connection to database.
	ConnectionShPtr m_connection;
	// Function which will be called when object will be destructing.
	ExpireCallback m_callback;
};


//
// Stores database connections and serves as a factory of ConnectionUnits.
//
class ConnectionPool
{
	//
	// Public interface.
	//
public:
	// Returns instance of ConnectionPool.
	ConnectionPool& Instance() const;
	// Returns RAII object for with database connection.
	ConnectionUnitUnPtr Acquire();

	//
	// Constraction and destruction.
	//
public:
	// minPoolSize - min size of conetcion pool.
	explicit ConnectionPool(std::size_t minPoolSize);

	//
	// Private methods.
	//
private:
	// Creates a new database connection.
	ConnectionShPtr CreateConnection(const std::string& config);
	// Removes connections which were been unused for a long time.
	void RemoveUnused();
	// Frees connection for using it again.
	void MakeConnectionFree(const ConnectionShPtr connection);

	//
	// Private data members.
	//
private:
	// Config for database connection.
	std::string m_config;
	// Min size of connection pool.
	std::size_t m_minPoolSize;
	// Timer for connection pool clearing.
	std::unique_ptr<timer::Timer> m_timer;
	// Mutes for thread safe working with pool.
	std::mutex m_mtx;
	// Connections which using for now.
	std::list<ConnectionShPtr> m_usedConnections;
	// Connections which free for now.
	std::list<ConnectionShPtr> m_freeConnections;
};


}	// namespace fmt::db