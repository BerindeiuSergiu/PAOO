#include "TimeStampedLogFile.hpp"
#include <iostream>

//basic cnst
TimeStampedLogFile::TimeStampedLogFile(const std::string& name)
    : LogFile(name), addTimestamp(false)
{
    std::cout << "[Constructor] TimeStampedLogFile created (no timestamp flag)\n";
}


TimeStampedLogFile::TimeStampedLogFile(const std::string& name, bool timestamp)
    : LogFile(name), addTimestamp(timestamp)
{
    std::cout << "[Constructor] TimeStampedLogFile created with timestamp=" 
              << (timestamp ? "true" : "false") << "\n";
}

// copy cnstr
TimeStampedLogFile::TimeStampedLogFile(const TimeStampedLogFile& other)
    : LogFile(other),                     // copying base class parts (i12)
      addTimestamp(other.addTimestamp)
{
    std::cout << "[Copy Constructor] TimeStampedLogFile\n";
}

// copy assignment (i10, i11, i12)
TimeStampedLogFile& TimeStampedLogFile::operator=(const TimeStampedLogFile& rhs)
{
    if (this == &rhs) return *this;       // self assignment

    LogFile::operator=(rhs);              // copying base class parts
    addTimestamp = rhs.addTimestamp;

    return *this;                         // return *this
}
