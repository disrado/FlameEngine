#include "pch.hpp"

#include "db/ConnectionPool.hpp"


namespace flm::db
{

namespace
{


static const std::size_t ConnectionsLifetime{ 60 };


std::string GetConfig()
{
	return fmt::format(
		"host={} port={} user={} password={} dbname={} connect_timeout=10",
		"localhost",
		"5432",
		"postgres",
		"postgres",
		"engine"
	);
}


}	// local namespace 


Connection::Connection(const std::string& config)
	: m_handle{ std::make_shared<Handle>(config) }
{}


HandleShPtr Connection::GetHandle() const
{
	return m_handle;
}


ConnectionUnit::ConnectionUnit(ConnectionShPtr connection, ExpireCallback callback)
	: m_connection{ connection }
	, m_callback{ callback }
{
}


ConnectionUnit::~ConnectionUnit()
{
	m_callback();
}


ConnectionShPtr ConnectionUnit::GetConnection() const
{
	return m_connection;
}


ConnectionPool& ConnectionPool::Instance() const
{
	static ConnectionPool instance{ 10 };
	return instance;
}


ConnectionUnitUnPtr ConnectionPool::Acquire()
{
	std::lock_guard{ m_mtx };

	ConnectionShPtr connection{ nullptr };

	if (m_freeConnections.empty())
	{
		connection = CreateConnection(m_config);
	}
	else
	{
		connection = m_freeConnections.back();
		m_freeConnections.pop_back();
		
	}
	
	m_usedConnections.push_back(connection);

	return std::make_unique<ConnectionUnit>(connection, [this, connection] {
		this->MakeConnectionFree(connection);
	});
}


ConnectionPool::ConnectionPool(std::size_t minPoolSize)
	: m_config{ GetConfig() }
	, m_minPoolSize{ minPoolSize }
	, m_timer{ nullptr }
{
	for(std::size_t i{ 0 }; i < m_minPoolSize; ++i) {
		m_freeConnections.push_back(CreateConnection(m_config));
	}

	m_timer = std::make_unique<timer::Timer>(
		timer::Timer::Seconds{ ConnectionsLifetime },
		[this] { this->RemoveUnused(); }
	);
	m_timer->Start();
}


ConnectionShPtr ConnectionPool::CreateConnection(const std::string& config)
{
	return std::make_shared<Connection>(config);
}


void ConnectionPool::RemoveUnused()
{
	std::lock_guard{ m_mtx };

	if (m_freeConnections.size() > m_minPoolSize) {
		m_freeConnections.erase(m_freeConnections.begin(), m_freeConnections.end());
	}
}


void ConnectionPool::MakeConnectionFree(const ConnectionShPtr connection)
{
	std::lock_guard{ m_mtx };

	const auto itr{ std::find(m_usedConnections.begin(), m_usedConnections.begin(), connection) };

	if (itr != m_usedConnections.end()) {
		m_usedConnections.erase(itr);
		m_freeConnections.push_back(*itr);
	}
}


}	// namespace flm::db