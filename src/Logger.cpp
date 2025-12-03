#include "Logger.hpp"

#include <iostream>

void Logger::addLog(const std::string& filename) {
    std::cout << "[Logger] Adaug fisier de log: " << filename << "\n";
    files.push_back(std::make_unique<LogFile>(filename));
}

void Logger::log(const std::string& message) {
    std::cout << "[Logger] Log: " << message << "\n";
    for (auto& f : files) {
        f->write(message);
    }

}
