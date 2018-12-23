#pragma once

#include <flame/db/Aliases.hpp>


namespace flm::db
{


// Holder for raw database connection.
class Connection
{
public:
	explicit Connection(const std::string& config);
	ShPtr<DbConnection> Get() const;

private:
	ShPtr<DbConnection> m_connection;
};


// Class for supporting RAII with database connections.
class ConnUnit
{
public:
	ConnUnit(ShPtr<Connection> connection, func<void()> callback);
	~ConnUnit();

	ConnUnit(ConnUnit&&) = default;
	ConnUnit& operator=(ConnUnit&&) = default;

	ConnUnit(const ConnUnit&) = delete;
	ConnUnit& operator=(const ConnUnit&) = delete;

public:
	ShPtr<DbConnection> Get() const;

private:
	ShPtr<Connection> m_connection;
	func<void()> m_callback;
};


// Stores database connections and serves as a factory of ConnUnits
class Pool
{
public:
	Pool& Inst() const;

	UnPtr<ConnUnit> Acquire();

private:
	explicit Pool(size_t minPoolSize);

private:
	ShPtr<Connection> CreateConnection(const std::string& config);
	void RemoveUnused();
	void Release(const ShPtr<Connection> connection);

private:
	std::string m_config;
	size_t m_minPoolSize;
	std::unique_ptr<utils::Timer> m_timer;
	std::mutex m_mtx;
	std::deque<ShPtr<Connection>> m_used;
	std::deque<ShPtr<Connection>> m_free;
};


} // namespace flm::db