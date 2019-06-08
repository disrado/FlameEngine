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
		lg::LOG(lg::Severity::error) << "Db connection was broken" << std::endl;
	}
	catch (...)
	{
		lg::LOG(lg::Severity::error) << "Worker creation error" << std::endl;
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