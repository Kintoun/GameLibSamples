#pragma once

#include "windows.h"
#include <sstream>

// For date and time
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

#define LOG(level) \
	if (level <= Util::Log::ReportLevel()) Util::Log().Get(level)

#define LOGERROR LOG(Util::LOG_ERROR)
#define LOGWARN LOG(Util::LOG_WARNING)
#define LOGINFO LOG(Util::LOG_INFO)
#define LOGDEBUG LOG(Util::LOG_DEBUG)
#define LOGDEBUG1 LOG(Util::LOG_DEBUG1)
#define LOGDEBUG2 LOG(Util::LOG_DEBUG2)
#define LOGDEBUG3 LOG(Util::LOG_DEBUG3)
#define LOGDEBUG4 LOG(Util::LOG_DEBUG4)

namespace Util {

// DEBUGN is N levels of indentation. Meant to be used for more details
enum LogLevel
{
	LOG_ERROR,
	LOG_WARNING,
	LOG_INFO,
	LOG_DEBUG,
	LOG_DEBUG1,
	LOG_LOG_DEBUG2,
	LOG_DEBUG3,
	LOG_DEBUG4,

	NUMITEMS
};

class Log
{
public:
	Log() {}
	~Log();

	std::ostringstream& Get(LogLevel level = LOG_INFO);
	static LogLevel ReportLevel() { return LOG_DEBUG4; }

protected:
	std::ostringstream os;

private:
	std::string NowTime();
	LogLevel logLevel;

	// non-copyable
	Log(const Log&);
	Log& operator =(const Log&);
};

} // namespace Util