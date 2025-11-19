#include "LogFile.hpp"

// constructor
LogFile::LogFile(const std::string& name)
    : filename(name), stream(new std::ofstream("logs/" + name, std::ios::app))
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

// deep copy constructor
LogFile::LogFile(const LogFile& other)
    : filename(other.filename + "_copy"),
      stream(new std::ofstream("logs/" + filename, std::ios::app))
{
    std::cout << "[Copy Constructor] Created copy: " << filename << "\n";
}

// move constructor
LogFile::LogFile(LogFile&& other) noexcept
    : filename(std::move(other.filename)), stream(other.stream)
{
    std::cout << "[Move Constructor] Moving LogFile " << filename << "\n";
    other.stream = nullptr;
}

// copy_assignment
LogFile& LogFile::operator=(const LogFile& rhs)
{

    if (this == &rhs) return *this; // self assignment

    std::cout << "[Copy Assignment] Assigning LogFile\n";

    // delete existing stream
    if (stream) {
        if (stream->is_open()) stream->close();
        delete stream;
    }

    //copyinh all parts
    filename = rhs.filename + "_copy_assign";
    stream = new std::ofstream("logs/" + filename, std::ios::app);

    return *this;
}

//move assignment
LogFile& LogFile::operator=(LogFile&& rhs) noexcept
{
    if (this == &rhs) return *this;

    std::cout << "[Move Assignment] Moving LogFile\n";

    // destroy current
    if (stream) {
        if (stream->is_open()) stream->close();
        delete stream;
    }

    filename = std::move(rhs.filename);
    stream = rhs.stream;

    rhs.stream = nullptr;

    return *this;
}

void LogFile::write(const std::string& message) {
    if (stream && stream->is_open()) {
        *stream << message << std::endl;
    }
}
