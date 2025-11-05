#pragma once
#include "LogFile.hpp"
#include <vector>

class Logger {
private:
    LogFile** files;   // vector de pointeri pe heap
    int count;

public:
    Logger();
    ~Logger();
    Logger(const Logger& other);
    Logger(Logger&& other) noexcept;
    void addLog(const std::string& filename);
    void log(const std::string& message);
};
