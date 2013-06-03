#include "Log.h"

namespace Util {

const char* s_logLevelString[NUMITEMS] = 
{
	"ERROR",
	"WARNING",
	"INFO",
	"DEBUG",
	"DEBUG1",
	"DEBUG2",
	"DEBUG3",
	"DEBUG4",
};

Log::~Log()
{
	os << std::endl;
	fprintf(stderr, "%s", os.str().c_str());
	OutputDebugStringA(os.str().c_str());
	// TODO: add file output here
	fflush(stderr);
}

std::string Log::NowTime()
{
	std::stringstream buffer;
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	std::stringstream output;
	std::tm tm = *std::localtime(&now_c);
	output << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
	return output.str();
}

std::ostringstream& Log::Get(LogLevel level)
{	
	os << "- " << NowTime();
	os << " " << s_logLevelString[level] << ": ";
	// indentation = more details
	os << std::string(level > LOG_DEBUG ? 0 : level - LOG_DEBUG, '\t');
	logLevel = level;
	return os;
}

} // namespace Util