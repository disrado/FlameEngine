#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>


namespace lg
{


enum Severity : uint8_t
{ 
	debug = 1,
	error = 2,
	info = 4,
	warning = 8,
};


namespace
{


typedef const std::string& CStrRef;

template<typename T>
using ShPtr = std::shared_ptr<T>;

using ForwardEntryFunc = std::function<void(ShPtr<std::ostringstream>)>;


} // namespace


class Logger;

class EntryCollector final
{
public:
	enum class Mode { process, ignore };

private:
	friend Logger;

	EntryCollector(Mode mode = Mode::process, ForwardEntryFunc forwardEntry = nullptr);

	EntryCollector(EntryCollector&&) = default;
	EntryCollector& operator =(EntryCollector&&) = default;

public:
	~EntryCollector();

	template<typename T>
	EntryCollector& operator<<(const T& message);
	EntryCollector& operator<<(std::ostream&(*os)(std::ostream&));

private:
	ForwardEntryFunc m_addEntryToQueue;
	ShPtr<std::ostringstream> m_entry;
	Mode m_mode;
};


class Logger final
{
public:
	static Logger& Instance();

	void setLoggedSeverities(int8_t severities);

	void setGlobalLogFile(CStrRef logFileName);

	EntryCollector log(CStrRef file, uint line, Severity sev);
	EntryCollector slog(CStrRef file, uint line, Severity sev, CStrRef scope);
	EntryCollector loggf(CStrRef file, uint line, Severity sev);
	EntryCollector logf(CStrRef file, uint line, Severity sev, CStrRef logFile);
	EntryCollector sloggf(CStrRef file, uint line, Severity sev, CStrRef scope);
	EntryCollector slogf(CStrRef file, uint line, Severity sev, CStrRef scope, CStrRef logFile);


private:
	Logger();
	~Logger();

	Logger(Logger&&) = delete;
	Logger(const Logger&) = delete;
	Logger& operator=(Logger&&) = delete;
	Logger& operator=(const Logger&) = delete;

	void addEntryToOSQueue(ShPtr<std::ostringstream> entry);
	void addEntryToOFSQueue(const std::string& fileName, ShPtr<std::ostringstream> entry);

	EntryCollector createEntryCollector(Severity severity, ForwardEntryFunc forwardEntry);

	void processOSEntries();
	void processOFSEntries();

private:
	bool m_isAlive;

	std::mutex m_osMtx;
	std::mutex m_ofsMtx;

	std::thread m_osThread;
	std::thread m_ofsThread;
	std::condition_variable m_osQueueCheck;
	std::condition_variable m_ofsQueueCheck;

	std::string m_logFileName;

	uint8_t m_loggedSeverities;
	std::queue<ShPtr<std::ostringstream>> m_OSEntries;
	std::queue<std::pair<std::string, ShPtr<std::ostringstream>>> m_OFSEntries;
};


#include "../../src/Logger.inl"


#define SET_GLOBAL_LOG_FILE(fileName) \
		Logger::Instance().setGlobalLogFile(fileName);

// simple log
// put message to std::cout
// [file:line] (severity) message
#define LOG(severity) \
			Logger::Instance().log(__FILE__, __LINE__, severity)


// LOG Global File
// put message to file, that has been set with Logger::setLogFileName
// [file:line] (severity) message 
#define LOGGF(severity) \
		Logger::Instance().loggf(__FILE__, __LINE__, severity)


// Scoped LOG
// put message to std::cout
// [file:line] (severity) {scope} message
#define SLOG(severity, scope) \
		Logger::Instance().slog(__FILE__, __LINE__, severity, scope)


// LOG File
// put message to file
// [file:line] (severity) message 
#define LOGF(severity, fileName) \
		Logger::Instance().logf(__FILE__, __LINE__, severity, fileName)


// Scoped LOG Global File
// scoped log
// put message to file, that has been set with Logger::setLogFileName
// [file:line] (severity) {scope} message
#define SLOGGF(severity, scope) \
		Logger::Instance().sloggf(__FILE__, __LINE__, severity, scope)


// Scoped LOG File
// put message to file
// [file:line] (severity) {scope} message
#define SLOGF(severity, scope, fileName) \
		Logger::Instance().slogf(__FILE__, __LINE__, severity, scope, fileName)


} // namespace l