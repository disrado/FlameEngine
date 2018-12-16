#include "pch.hpp"

#include "db/Worker.hpp"


namespace flm::db
{


Worker::Worker(ConnUnitShPtr connection)
{
	Init(connection);
}


Worker::Worker(ConnUnitUnPtr connection)
{
	Init(std::move(connection));
}


void Worker::Init(ConnUnitShPtr connection)
{
	m_connection = connection;

	try
	{
		m_work = std::make_shared<pqxx::work>(*(connection->GetHandle()));
	}
	catch (const pqxx::broken_connection& ex)
	{
		throw std::runtime_error{ "Db connection was broken" };
	}
	catch (...)
	{
		throw std::runtime_error{ "Worker creation error" };
	}
}


Result Worker::Execute(const std::string& query) const
{
	return m_work->exec(query);
}


void Worker::Commit() const
{
	m_work->commit();
}


std::string Worker::Esc(const std::string& str) const
{
	return m_work->esc(str);
}

}	// namespace flm::db