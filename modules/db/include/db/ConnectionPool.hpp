#pragma once

#include "db/Types.hpp"


namespace flm::db
{


class Connection
{
public:
	Connection(const std::string& config);

	void SetUsed();
	void SetUnused();

	bool InUse() const;

	HandleShPtr GetHandle() const;

private:
	bool m_inUse;
	HandleShPtr m_handle;
};

using ConnectionShPtr = std::shared_ptr<Connection>;


class ConnectionPool;


class ConnectionUnit
{
public:
	using ExpirCallback = std::function<void()>;

public:
	explicit ConnectionUnit(ConnectionShPtr connection);
	~ConnectionUnit();

	ConnectionUnit(const ConnectionUnit&) = delete;
	ConnectionUnit(ConnectionUnit&&) = delete;
	ConnectionUnit& operator=(const ConnectionUnit&) = delete;
	ConnectionUnit& operator=(ConnectionUnit&&) = delete;

	ConnectionShPtr GetConnection() const;
	void SetCallback(ExpirCallback dieCallback);

private:
	ExpirCallback m_dieCallback;
	ConnectionShPtr m_connection;
};

using ConnectionUnitShPtr = std::shared_ptr<ConnectionUnit>;
using ConnectionUnitUnPtr = std::unique_ptr<ConnectionUnit>;


class ConnectionPool
{
public:
	ConnectionPool& Instance() const;
	ConnectionUnitUnPtr Acquire();

private:
	explicit ConnectionPool(std::size_t minPoolSize);
	ConnectionShPtr Extend();
	ConnectionShPtr CreateConnection();
	void RemoveUnused();
	void MakeConnectionFree(const ConnectionShPtr connection);

private:
	std::size_t m_minPoolSize;
	std::unique_ptr<timer::Timer> m_timer;
	std::mutex m_usedListMtx;
	std::mutex m_freeListMtx;
	std::list<ConnectionShPtr> m_usedConnections;
	std::list<ConnectionShPtr> m_freeConnections;
};


}	// namespace fmt::db