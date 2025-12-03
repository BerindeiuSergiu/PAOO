#pragma once

#include <fstream>
#include <string>
#include <iostream>

class LogFile {
public:
    explicit LogFile(std::string name);
    ~LogFile();

    // unique - copie interzista
    LogFile(const LogFile&) = delete;
    LogFile& operator=(const LogFile&) = delete;

    // poti muta
    LogFile(LogFile&& other) noexcept;
    LogFile& operator=(LogFile&& other) noexcept;

    void write(const std::string& message);

    const std::string& name() const noexcept { return filename; }

private:
    std::string filename;
    std::ofstream stream;
};
