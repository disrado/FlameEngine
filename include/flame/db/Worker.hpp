#pragma once

#include <flame/db/Aliases.hpp>


namespace flm::db
{


class ConnUnit;


// Provides access to database
class Worker
{
public:
	Worker(ShPtr<ConnUnit> connection);
	Worker(UnPtr<ConnUnit> connection);
	virtual ~Worker() = default;

public:
	void Commit() const;

protected:
	DbResult Execute(const std::string& query) const;
	std::string Escape(const std::string& str) const;
	
private:
	void Init(ShPtr<ConnUnit> connection);

private:
	ShPtr<ConnUnit> m_connection;
	ShPtr<pqxx::work> m_work;
};


} // namespace flm::db