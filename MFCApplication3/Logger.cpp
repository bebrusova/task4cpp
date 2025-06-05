#include "Logger.h"
#include <ctime>
#include <iomanip>
#include <sstream>

std::mutex Logger::logMutex;
std::ofstream Logger::logFile;

void Logger::Init()
{
    if (!logFile.is_open())
    {
        logFile.open("log.txt", std::ios::app);
    }
}

void Logger::Log(const std::string& level, const std::string& message)
{
    std::lock_guard<std::mutex> lock(logMutex);

    Init();

    if (logFile.is_open())
    {
        std::time_t t = std::time(nullptr);
        std::tm localTime;
#ifdef _WIN32
        localtime_s(&localTime, &t);
#else
        localtime_r(&t, &localTime);
#endif

        std::ostringstream oss;
        oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");

        logFile << "[" << oss.str() << "] [" << level << "] " << message << std::endl;
        logFile.flush(); 
    }
}
