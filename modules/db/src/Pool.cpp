#include "pch.hpp"

#include "db/Pool.hpp"


namespace flm::db
{

namespace
{


static const std::size_t ConnectionsLifetime{ 60 };
static const std::size_t MinPoolSize{ 10 };


std::string GetDbConfig()
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


HandleShPtr ConnectionUnit::GetHandle() const
{
	return m_connection->GetHandle();
}


Pool& Pool::Instance() const
{
	static Pool instance{ MinPoolSize };
	return instance;
}


ConnUnitUnPtr Pool::Acquire()
{
	std::lock_guard{ m_mtx };

	ConnectionShPtr connection{ nullptr };

	if (m_free.empty())
	{
		connection = CreateConnection(m_config);
	}
	else
	{
		connection = m_free.back();
		m_free.pop_back();
	}
	
	m_used.push_back(connection);

	return std::make_unique<ConnectionUnit>(connection, [this, connection] {
		this->MakeConnectionFree(connection);
	});
}


Pool::Pool(std::size_t minPoolSize)
	: m_config{ GetDbConfig() }
	, m_minPoolSize{ minPoolSize }
	, m_timer{ nullptr }
{
	for (std::size_t i{ 0 }; i < m_minPoolSize; ++i) {
		m_free.push_back(CreateConnection(m_config));
	}

	m_timer = std::make_unique<timer::Timer>(
		timer::Timer::Seconds{ ConnectionsLifetime },
		[this] { this->RemoveUnused(); }
	);
	m_timer->Start();
}


ConnectionShPtr Pool::CreateConnection(const std::string& config)
{
	return std::make_shared<Connection>(config);
}


void Pool::RemoveUnused()
{
	std::lock_guard{ m_mtx };

	if (m_free.size() > m_minPoolSize) {
		m_free.erase(m_free.begin() + m_minPoolSize, m_free.end());
	}
}


void Pool::MakeConnectionFree(const ConnectionShPtr connection)
{
	std::lock_guard{ m_mtx };

	const auto itr{ std::find(m_used.begin(), m_used.begin(), connection) };

	if (itr != m_used.end()) {
		m_used.erase(itr);
		m_free.push_back(*itr);
	}
}


}	// namespace flm::db