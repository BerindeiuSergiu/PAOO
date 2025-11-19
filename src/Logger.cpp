#include "Logger.hpp"
#include <iostream>

// constructor
Logger::Logger() : files(nullptr), count(0) {
    std::cout << "[Constructor] Logger created\n";
}

// destructor
Logger::~Logger() {
    std::cout << "[Destructor] Cleaning up Logger\n";
    for (int i = 0; i < count; ++i)
        delete files[i];
    delete[] files;
}

// deep copy constructor
Logger::Logger(const Logger& other)
    : count(other.count)
{
    std::cout << "[Copy Constructor] Copying Logger\n";

    files = new LogFile*[count];
    for (int i = 0; i < count; ++i)
        files[i] = new LogFile(*other.files[i]); 
}

// move constructor
Logger::Logger(Logger&& other) noexcept
    : files(other.files), count(other.count)
{
    std::cout << "[Move Constructor] Moving Logger\n";
    other.files = nullptr;
    other.count = 0;
}

// copy assign
Logger& Logger::operator=(const Logger& rhs)
{


    if (this == &rhs) return *this; // self assign

    std::cout << "[Copy Assignment] Logger\n";

    // cleanup current data
    for (int i = 0; i < count; ++i)
        delete files[i];
    delete[] files;

    /*
    // copy all parts
    */
    count = rhs.count;
    files = new LogFile*[count];
    for (int i = 0; i < count; ++i)
        files[i] = new LogFile(*rhs.files[i]);

    return *this;
}

//move
Logger& Logger::operator=(Logger&& rhs) noexcept
{
    if (this == &rhs) return *this;

    std::cout << "[Move Assignment] Logger\n";

    // cleanup old
    for (int i = 0; i < count; ++i)
        delete files[i];
    delete[] files;

    // transfer ownership
    files = rhs.files;
    count = rhs.count;

    rhs.files = nullptr;
    rhs.count = 0;

    return *this;
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
