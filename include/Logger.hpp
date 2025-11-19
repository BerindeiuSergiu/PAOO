#pragma once
#include "LogFile.hpp"

class Logger {
private:
    LogFile** files;
    int count;

public:
    Logger();
    ~Logger();
    Logger(const Logger& other);
    Logger(Logger&& other) noexcept;

    Logger& operator=(const Logger& rhs);     // copy assignment
    Logger& operator=(Logger&& rhs) noexcept; // move assignment

    void addLog(const std::string& filename);
    void log(const std::string& message);
};
