#include "pch.hpp"

#include <flame/db/Worker.hpp>

#include <flame/db/Pool.hpp>


namespace flm::db
{


Worker::Worker(ShPtr<ConnUnit> connection)
{
	Init(connection);
}


Worker::Worker(UnPtr<ConnUnit> connection)
{
	Init(std::move(connection));
}


void Worker::Init(ShPtr<ConnUnit> connection)
{
	m_connection = connection;

	try {
		m_work = std::make_shared<pqxx::work>(*(connection->Get()));
	} catch (const pqxx::broken_connection& ex) {
		throw std::runtime_error{ "Db connection was broken" };
	} catch (...) {
		throw std::runtime_error{ "Worker creation error" };
	}
}


DbResult Worker::Execute(const std::string& query) const
{
	return m_work->exec(query);
}


void Worker::Commit() const
{
	m_work->commit();
}


std::string Worker::Escape(const std::string& str) const
{
	return m_work->esc(str);
}


} // namespace flm::db