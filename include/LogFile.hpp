#pragma once
#include <iostream>
#include <fstream>
#include <string>

class LogFile {
private:
    std::string filename;
    std::ofstream* stream; 

public:
    LogFile(const std::string& name);
    ~LogFile();
    LogFile(const LogFile& other);
    LogFile(LogFile&& other) noexcept;

    LogFile& operator=(const LogFile& rhs);     // copy assignment
    LogFile& operator=(LogFile&& rhs) noexcept; // move assignment

    void write(const std::string& message);
    std::string getName() const { return filename; }
};
