#pragma once
#include "LogFile.hpp"      
#include <string>           
#include <iostream>         

class TimeStampedLogFile : public LogFile {
private:
    bool addTimestamp;

public:
    TimeStampedLogFile(const std::string& name, bool timestamp);  
    TimeStampedLogFile(const std::string& name);                   
    TimeStampedLogFile(const TimeStampedLogFile& other);           // copy constructor (i12)
    TimeStampedLogFile& operator=(const TimeStampedLogFile& rhs);  // copy assignment (i10, i11, i12)
};
