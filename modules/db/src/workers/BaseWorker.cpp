#include "pch.hpp"

#include "db/workers/BaseWorker.hpp"


namespace flm::db
{


BaseWork::BaseWork(ConnectionUnitShPtr connection)
{
	Init((connection));
}


BaseWork::BaseWork(ConnectionUnitUnPtr connection)
{
	Init(std::move(connection));
}


void BaseWork::Init(ConnectionUnitShPtr connection)
{
	m_connection = connection;

	try
	{
		m_work = std::make_shared<pqxx::work>(*(connection->GetConnection()->GetHandle()));
	}
	catch (const pqxx::broken_connection& ex)
	{
		lg::LOG(lg::Severity::error) << "Db connection was broken" << std::endl;
	}
	catch (...)
	{
		lg::LOG(lg::Severity::error) << "Db work creation error" << std::endl;
	}
}


Result BaseWork::Execute(const std::string& query) const
{
	return m_work->exec(query);
}


void BaseWork::Commit() const
{
	m_work->commit();
}


std::string BaseWork::Esc(const std::string& str) const
{
	return m_work->esc(str);
}

}	// namespace flm::db