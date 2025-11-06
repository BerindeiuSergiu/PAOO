#include "LogFile.hpp"

LogFile::LogFile(const std::string& name)
    :filename(name), stream(new std::ofstream("logs/" + name, std::ios::app))
{
    std::cout << "[Constructor] LogFile created: " << filename << "\n";
}

// destructor
LogFile::~LogFile() {
    std::cout << "[Destructor] Closing file: " << filename << "\n";
    if (stream) {
        if (stream->is_open()) stream->close();
        delete stream;
    }
}

// copy constructor method -> deep copy
LogFile::LogFile(const LogFile& other)
    : filename(other.filename + "_copy"), stream(new std::ofstream("logs/" + filename, std::ios::app))
{
    std::cout << "[Copy Constructor] Created a copy: " << filename << "\n";
}

// move constr
LogFile::LogFile(LogFile&& other) noexcept
    : filename(std::move(other.filename)), stream(other.stream)
{
    std::cout << "[Move Constructor] Moving log file: " << filename << "\n";
    other.stream = nullptr;
}

void LogFile::write(const std::string& message) {
    if (stream && stream->is_open()) {
        *stream << message << std::endl;
    }
}
