#pragma once
#include <iostream>
#include <fstream>
#include <string>

class LogFile {
private:
    std::string filename;
    std::ofstream* stream; // alocat pe heap

public:
    LogFile(const std::string& name);
    ~LogFile();
    LogFile(const LogFile& other);
    LogFile(LogFile&& other) noexcept;
    void write(const std::string& message);
    std::string getName() const { return filename; }
};
