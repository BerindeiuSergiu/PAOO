#include "ThreadSafeLogger.hpp"
#include <iostream>
#include <chrono>

ThreadSafeLogger::ThreadSafeLogger(const std::string& logFile)
    : logger(std::make_shared<Logger>()), shouldStop(false), error(false) {
    logger->addLog(logFile);
    workerThread = std::thread(&ThreadSafeLogger::processMessages, this);
}

ThreadSafeLogger::~ThreadSafeLogger() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        shouldStop = true;
    }
    cv.notify_one();
    if (workerThread.joinable()) {
        workerThread.join();
    }
}

ThreadSafeLogger::ThreadSafeLogger(const ThreadSafeLogger& other)
    : logger(other.logger), shouldStop(false), error(false) {
    std::lock_guard<std::mutex> lock(const_cast<ThreadSafeLogger&>(other).queueMutex);
    workerThread = std::thread(&ThreadSafeLogger::processMessages, this);
}

ThreadSafeLogger& ThreadSafeLogger::operator=(const ThreadSafeLogger& other) {
    if (this != &other) {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            shouldStop = true;
        }
        cv.notify_one();
        if (workerThread.joinable()) {
            workerThread.join();
        }
        
        logger = other.logger;
        shouldStop = false;
        error = false;
        errorMessage.clear();
        workerThread = std::thread(&ThreadSafeLogger::processMessages, this);
    }
    return *this;
}

void ThreadSafeLogger::asyncLog(const std::string& message) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        messageQueue.push(message);
    }
    cv.notify_one();
}

void ThreadSafeLogger::processMessages() {
    try {
        while (true) {
            std::unique_lock<std::mutex> lock(queueMutex);
            cv.wait_for(lock, std::chrono::milliseconds(100), [this] { 
                return !messageQueue.empty() || shouldStop; 
            });
            
            while (!messageQueue.empty()) {
                std::string message = messageQueue.front();
                messageQueue.pop();
                lock.unlock();
                
                if (!message.empty()) {
                    logger->log(message);
                }
                
                lock.lock();
            }
            
            if (shouldStop && messageQueue.empty()) {
                break;
            }
        }
    } catch (const std::exception& e) {
        std::lock_guard<std::mutex> lock(errorMutex);
        error = true;
        errorMessage = std::string("Thread error: ") + e.what();
    }
}

void ThreadSafeLogger::waitForCompletion() {
    std::unique_lock<std::mutex> lock(queueMutex);
    cv.wait_for(lock, std::chrono::seconds(5), [this] { return messageQueue.empty(); });
}

bool ThreadSafeLogger::hasError() const {
    std::lock_guard<std::mutex> lock(errorMutex);
    return error;
}

std::string ThreadSafeLogger::getErrorMessage() const {
    std::lock_guard<std::mutex> lock(errorMutex);
    return errorMessage;
}