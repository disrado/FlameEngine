#include "../pch.hpp"

#include "db/workers/BaseWorker.hpp"

#include <iostream>


namespace flm::db
{


BaseWork::BaseWork(ConnectionUnitShPtr connection)
	: m_connection{ connection }
{
	try
	{
		m_work = std::make_shared<pqxx::work>(*(connection->GetConnection()->GetHandle()));
	}
	catch(const pqxx::broken_connection& ex)
	{
		// TODO: replace by log.
		std::cout << "Connection was broken" << std::endl;
	}
}


Result BaseWork::Exec(const std::string& query) const
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