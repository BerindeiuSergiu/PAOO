#ifndef THREADSAFELOGGER_HPP
#define THREADSAFELOGGER_HPP

#include "Logger.hpp"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>

class ThreadSafeLogger {
public:
    explicit ThreadSafeLogger(const std::string& logFile);
    ~ThreadSafeLogger();
    
    ThreadSafeLogger(const ThreadSafeLogger& other);
    ThreadSafeLogger& operator=(const ThreadSafeLogger& other);
    
    void asyncLog(const std::string& message);
    void waitForCompletion();
    bool hasError() const;
    std::string getErrorMessage() const;

private:
    std::shared_ptr<Logger> logger;
    std::queue<std::string> messageQueue;
    mutable std::mutex queueMutex;
    std::condition_variable cv;
    std::thread workerThread;
    bool shouldStop;
    mutable std::mutex errorMutex;
    bool error;
    std::string errorMessage;
    
    void processMessages();
};

#endif