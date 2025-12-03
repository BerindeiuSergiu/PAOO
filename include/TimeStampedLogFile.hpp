#pragma once
#include "LogFile.hpp"
#include <string>

class TimeStampedLogFile : public LogFile {
public:
    explicit TimeStampedLogFile(std::string name,
                                bool withTimestamp = true);


    TimeStampedLogFile(const TimeStampedLogFile&) = delete;
    TimeStampedLogFile& operator=(const TimeStampedLogFile&) = delete;

    TimeStampedLogFile(TimeStampedLogFile&&) noexcept = default;
    TimeStampedLogFile& operator=(TimeStampedLogFile&&) noexcept = default;

    void write(const std::string& message);

private:
    bool addTimestamp;
};
