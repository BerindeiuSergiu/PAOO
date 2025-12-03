#pragma once

#include "LogFile.hpp"
#include "TimeStampedLogFile.hpp"

#include <memory>
#include <vector>
#include <string>


class Logger {
public:
    Logger()  = default;
    ~Logger() = default;

    // copy - intezis
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    Logger(Logger&&) noexcept = default;
    Logger& operator=(Logger&&) noexcept = default;

    // add log file
void addLog(const std::string& filename);
    void log(const std::string& message);

private:
    std::vector<std::unique_ptr<LogFile>> files;
};
