#include "Logger.hpp"
#include <utility>
#include <vector>
#include <string>


Logger createCustomLogger(const std::vector<std::string>& logFiles, const std::string& initialMessage) {
    Logger logger;
    for(const auto& file : logFiles) {
        logger.addLog(file);
    }
    if(!initialMessage.empty()) {
        logger.log(initialMessage);
    }
    return logger;
}

int main() {
    std::cout << "=== Logger Factory Demo Start ===\n";

    // testing files
    std::vector<std::string> logFiles1 = {"system.log", "debug.log"};
    Logger systemLogger = createCustomLogger(logFiles1, "System logger initialized");
    systemLogger.log("System is running normally");

    // testing configs
    std::vector<std::string> logFiles2 = {"errors.log"};
    Logger errorLogger = createCustomLogger(logFiles2, "Error logger initialized");
    errorLogger.log("Error logging system active");

    Logger _backupErrorLogger = errorLogger; // testing copy
    errorLogger.log("This is an error message from the original logger");
    _backupErrorLogger.log("This is an error message from the backup logger");

    // testing no msg
    std::vector<std::string> logFiles3 = {"audit.log", "trace.log"};
    Logger auditLogger = createCustomLogger(logFiles3, "");
    auditLogger.log("First audit entry");

    std::cout << "=== Logger Factory Demo End ===\n";
    return 0;
}
