#include "pch.hpp"

#include <flame/db/Pool.hpp>


namespace flm::db
{
namespace
{


static const size_t ConnectionsLifetime{ 60 };
static const size_t MinPoolSize{ 10 };


std::string GetDbConfig()
{
	return
		"host=localhost "
		"port=5432 "
		"user=postgres "
		"password=postgres "
		"dbname=engine "
		"connect_timeout=10";
}


} // local namespace


Connection::Connection(const std::string& config)
	: m_connection{ std::make_shared<DbConnection>(config) }
{}


ShPtr<DbConnection> Connection::Get() const
{
	return m_connection;
}


ConnUnit::ConnUnit(ShPtr<Connection> connection, func<void()> callback)
	: m_connection{ connection }
	, m_callback{ callback }
{}


ConnUnit::~ConnUnit()
{
	m_callback();
}


ShPtr<DbConnection> ConnUnit::Get() const
{
	return m_connection->Get();
}


Pool& Pool::Inst()
{
	static Pool instance{ MinPoolSize };
	return instance;
}


UnPtr<ConnUnit> Pool::Acquire()
{
	std::lock_guard{ m_mtx };

	ShPtr<Connection> connection{ nullptr };

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

	return std::make_unique<ConnUnit>(connection, [this, connection] {
		this->Release(connection);
	});
}


Pool::Pool(size_t minPoolSize)
	: m_config{ GetDbConfig() }
	, m_minPoolSize{ minPoolSize }
	, m_timer{ nullptr }
{
	for (size_t i{ 0 }; i < m_minPoolSize; ++i) {
		m_free.push_back(CreateConnection(m_config));
	}

	m_timer = std::make_unique<utils::Timer>(
		Seconds{ ConnectionsLifetime },
		[this] { this->RemoveUnused(); }
	);
	m_timer->Start();
}


ShPtr<Connection> Pool::CreateConnection(const std::string& config)
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


void Pool::Release(const ShPtr<Connection> connection)
{
	std::lock_guard{ m_mtx };

	const auto itr{ std::find(m_used.begin(), m_used.end(), connection) };

	if (itr != m_used.end())
	{
		m_free.push_back(*itr);
		m_used.erase(itr);
	}
}


} // namespace flm::db