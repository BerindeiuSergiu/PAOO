#include "TimeStampedLogFile.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

TimeStampedLogFile::TimeStampedLogFile(std::string name, bool withTimestamp)
    : LogFile(std::move(name)),
      addTimestamp(withTimestamp)
{
    std::cout << "[TimeStampedLogFile ctor] withTimestamp=" 
              << std::boolalpha << addTimestamp << "\n";
}

void TimeStampedLogFile::write(const std::string& message) {
    if (!addTimestamp) {
        LogFile::write(message);
        return;
    }

    using clock = std::chrono::system_clock;
    auto now    = clock::now();
    std::time_t t = clock::to_time_t(now);

    std::tm tm{};
#if defined(_WIN32)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif

    std::ostringstream oss;
    oss << '[' << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "] " << message;

    LogFile::write(oss.str());
}
