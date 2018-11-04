#include "pch.hpp"

#include "db/ConnectionPool.hpp"


namespace flm::db
{


Connection::Connection(const std::string& config)
{
	m_handle = std::make_shared<Handle>(config);
}


void Connection::SetUsed()
{
	m_inUse = true;
}


void Connection::SetUnused()
{
	m_inUse = false;
}


bool Connection::InUse() const
{
	return m_inUse;
}


HandleShPtr Connection::GetHandle() const
{
	return m_handle;
}


ConnectionUnit::ConnectionUnit(ConnectionShPtr connection)
	: m_connection{ connection }
{
	
	m_connection->SetUsed();
}


ConnectionUnit::~ConnectionUnit()
{
	m_connection->SetUnused();
	m_dieCallback();
}


ConnectionShPtr ConnectionUnit::GetConnection() const
{
	return m_connection;
}


void ConnectionUnit::SetCallback(ExpirCallback dieCallback)
{
	m_dieCallback = dieCallback;
}


ConnectionPool& ConnectionPool::Instance() const
{
	static ConnectionPool instance{ 10 };
	return instance;
}


ConnectionUnitUnPtr ConnectionPool::Acquire()
{
	ConnectionUnitUnPtr unit{ nullptr };

	if (!m_freeConnections.empty())
	{
		m_usedConnections.push_back(m_freeConnections.back());
		m_freeConnections.pop_back();

		unit = std::make_unique<ConnectionUnit>(m_usedConnections.back());
	} 
	else
	{
		m_usedConnections.push_back(Extend());
		unit = std::make_unique<ConnectionUnit>(m_usedConnections.back());
	}

	unit->SetCallback([this, connection = unit->GetConnection()] {
		this->MakeConnectionFree(connection);
	});

	return unit;
}


ConnectionPool::ConnectionPool(std::size_t minPoolSize)
	: m_minPoolSize{ minPoolSize }
	, m_timer{ nullptr }
{
	for(std::size_t i{ 0 }; i < m_minPoolSize; ++i) {
		m_freeConnections.push_back(Extend());
	}

	m_timer = std::make_unique<timer::Timer>(
		timer::Timer::Seconds{ 60 },
		[this] { this->RemoveUnused(); }
	);
	m_timer->Start();
}


ConnectionShPtr ConnectionPool::Extend()
{
	return CreateConnection();
}


ConnectionShPtr ConnectionPool::CreateConnection()
{
	const auto config{ fmt::format(
		"host={} port={} user={} password={} dbname={} connect_timeout=10",
		"localhost",
		"5432",
		"postgres",
		"postgres",
		"engine")
	};

	return std::make_shared<Connection>(config);
}


void ConnectionPool::RemoveUnused()
{
	if (m_freeConnections.size() > m_minPoolSize) {
		m_freeConnections.erase(m_freeConnections.begin(), m_freeConnections.end());
	}
}


void ConnectionPool::MakeConnectionFree(const ConnectionShPtr connection)
{
	const auto itr{ std::find(m_usedConnections.begin(), m_usedConnections.begin(), connection) };

	if (itr != m_usedConnections.end()) {
		m_usedConnections.erase(itr);
		m_freeConnections.push_back(*itr);
	}
}


}	// namespace flm::db