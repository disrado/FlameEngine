#pragma once

#include "db/Types.hpp"


namespace flm::db
{


class Connection;
using ConnectionShPtr = std::shared_ptr<Connection>;


class ConnectionUnit;
using ConnUnitShPtr = std::shared_ptr<ConnectionUnit>;
using ConnUnitUnPtr = std::unique_ptr<ConnectionUnit>;


//
// Holder for database connection.
//
class Connection
{
public:
	// config - config for database connection.
	explicit Connection(const std::string& config);

public:
	// Returns raw database connection handle.
	HandleShPtr GetHandle() const;

private:
	// Raw database connection handle.
	HandleShPtr m_handle;
};


//
// Class for supporting RAII with database connections.
//
class ConnectionUnit
{
public:
	using ExpireCallback = std::function<void()>;

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

public:
	// Returns raw database connection handle.
	HandleShPtr GetHandle() const;

private:
	// Connection to database.
	ConnectionShPtr m_connection;
	// Function which will be called when object will be destructing.
	ExpireCallback m_callback;
};


//
// Stores database connections and serves as a factory of ConnectionUnits.
//
class Pool
{
public:
	// Returns instance of Pool.
	Pool& Instance() const;
	// Returns RAII object for with database connection.
	ConnUnitUnPtr Acquire();

public:
	// minPoolSize - min size of conetcion pool.
	explicit Pool(std::size_t minPoolSize);

private:
	// Creates a new database connection.
	ConnectionShPtr CreateConnection(const std::string& config);
	// Removes connections which were been unused for a long time.
	void RemoveUnused();
	// Frees connection for using it again.
	void MakeConnectionFree(const ConnectionShPtr connection);

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
	std::deque<ConnectionShPtr> m_used;
	// Connections which free for now.
	std::deque<ConnectionShPtr> m_free;
};


}	// namespace fmt::db