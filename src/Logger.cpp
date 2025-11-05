#include "Logger.hpp"

Logger::Logger() : files(nullptr), count(0) {
    std::cout << "[Constructor] Logger created\n";
}

// destr
Logger::~Logger() {
    std::cout << "[Destructor] Cleaning up Logger\n";
    for (int i = 0; i < count; ++i)
        delete files[i];
    delete[] files;
}

// copy constr --> deep cpy
Logger::Logger(const Logger& other) : count(other.count) {
    std::cout << "[Copy Constructor] Copying Logger\n";
    files = new LogFile*[count];
    for (int i = 0; i < count; ++i) {
        files[i] = new LogFile(*other.files[i]); // copy each file
    }
}

// mv constr
Logger::Logger(Logger&& other) noexcept
    : files(other.files), count(other.count)
{
    std::cout << "[Move Constructor] Moving Logger\n";
    other.files = nullptr;
    other.count = 0;
}

void Logger::addLog(const std::string& filename) {
    LogFile** newFiles = new LogFile*[count + 1];
    for (int i = 0; i < count; ++i)
        newFiles[i] = files[i];

    newFiles[count] = new LogFile(filename);
    delete[] files;
    files = newFiles;
    count++;
}

void Logger::log(const std::string& message) {
    for (int i = 0; i < count; ++i)
        files[i]->write(message);
}
