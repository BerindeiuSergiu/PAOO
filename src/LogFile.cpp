#include "LogFile.hpp"

#include <stdexcept>

LogFile::LogFile(std::string name)
    : filename(std::move(name)),
      stream("logs/" + filename, std::ios::app)
{
    std::cout << "[LogFile ctor] Opening: " << filename << "\n";
    if (!stream.is_open()) {
        throw std::runtime_error("Cannot open log file: " + filename);
    }
}

LogFile::~LogFile() {
    std::cout << "[LogFile dtor] Closing: " << filename << "\n";
}

// move cnstor
LogFile::LogFile(LogFile&& other) noexcept
    : filename(std::move(other.filename)),
      stream(std::move(other.stream))
{
    std::cout << "[LogFile move ctor] Moving: " << filename << "\n";
}

// move assign
LogFile& LogFile::operator=(LogFile&& other) noexcept {
    if (this != &other) {
        std::cout << "[LogFile move assign] " << filename << " <- " << other.filename << "\n";

        if (stream.is_open())
            stream.close();

        filename = std::move(other.filename);
        stream   = std::move(other.stream);
    }
    return *this;
}

void LogFile::write(const std::string& message) {
    if (!stream.is_open()) {
        throw std::runtime_error("Writing to closed log file: " + filename);
    }

    stream << message << '\n';
    stream.flush();
}
