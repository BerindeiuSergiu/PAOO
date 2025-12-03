#include "Logger.hpp"
#include "TimeStampedLogFile.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <thread>
#include <mutex>
#include <fstream>
#include <chrono>

// ---------------------------------------------------------
// Struct comună pentru demo de thread-uri
// ---------------------------------------------------------
struct SharedLogResource {
    std::string filename;
};

std::ofstream globalOut;   // folosit simultan de writer A și B fără mutex!

void unsafeWriterA(std::shared_ptr<SharedLogResource> shared) {
    for (int i = 0; i < 10; i++) {

        // folosesc exact același stream global
        globalOut << "[A PART1] line " << i << " --- XXXXXXXX";
        std::this_thread::sleep_for(std::chrono::microseconds(1));
        globalOut << "YYYYYYYY END_A\n";
    }
}

void unsafeWriterB(std::shared_ptr<SharedLogResource> shared) {
    for (int i = 0; i < 10; i++) {

        globalOut << "[B PART1] line " << i << " --- 11111111";
        std::this_thread::sleep_for(std::chrono::microseconds(1));
        globalOut << "22222222 END_B\n";
    }
}

// ------------------------
// UNSAFE READER
// ------------------------
void unsafeReader(std::shared_ptr<SharedLogResource> shared) {
    for (int i = 0; i < 10; i++) {
        std::ifstream in(shared->filename);
        int lineCount = 0;
        std::string line;
        while (std::getline(in, line)) {
            ++lineCount;
        }
        std::cout << "[UNSAFE READER] citit " << lineCount
                  << " linii din " << shared->filename << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

// ---------------------------------------------------------
// DEMO UNSAFE — două writer thread-uri care se CIOMĂGESC
// ---------------------------------------------------------
void runUnsafeDemoDual() {
    std::cout << "\n=== DEMO THREAD-URI NESINCRONIZATE (FARA MUTEX) ===\n";

    auto sharedRes = std::make_shared<SharedLogResource>();
    sharedRes->filename = "logs/threads_unsafe.log";

    {
        std::ofstream clear(sharedRes->filename, std::ios::trunc);
    }

    // DESCHIDEM O SINGURĂ DATĂ — stream împărțit de 2 threaduri!
    globalOut.open(sharedRes->filename, std::ios::app);

    std::thread tA(unsafeWriterA, sharedRes);
    std::thread tB(unsafeWriterB, sharedRes);

    tA.join();
    tB.join();

    globalOut.close();

    std::cout << ">> CORUPERE GARANTATA: thread-urile au scris simultan în acelasi stream.\n";
}


// ------------------------
// DEMO SAFE CU MUTEX
// ------------------------
void safeWriter(std::shared_ptr<SharedLogResource> shared, std::mutex& mtx) {
    for (int i = 0; i < 10; ++i) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::ofstream out(shared->filename, std::ios::app);
            out << "[SAFE WRITER] line " << i << "\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }
}

void safeReader(std::shared_ptr<SharedLogResource> shared, std::mutex& mtx) {
    for (int i = 0; i < 10; ++i) {
        int lineCount = 0;
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::ifstream in(shared->filename);
            std::string line;
            while (std::getline(in, line)) {
                ++lineCount;
            }
        }
        std::cout << "[SAFE READER] citit " << lineCount
                  << " linii din " << shared->filename << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void runSafeDemo() {
    std::cout << "\n=== DEMO THREAD-URI SINCRONIZATE (CU MUTEX) ===\n";

    auto sharedRes = std::make_shared<SharedLogResource>();
    sharedRes->filename = "logs/threads_safe.log";

    {
        std::ofstream clear(sharedRes->filename, std::ios::trunc);
    }

    std::mutex mtx;

    std::thread writer(safeWriter, sharedRes, std::ref(mtx));
    std::thread reader(safeReader, sharedRes, std::ref(mtx));

    writer.join();
    reader.join();

    std::cout << ">> TOTUL E SINCRONIZAT cu mutex.\n";
}

// ---------------------------------------------------------
// Logger + TimeStampedLogFile
// ---------------------------------------------------------

Logger createCustomLogger(const std::vector<std::string>& logFiles,
                          const std::string& initialMessage)
{
    Logger logger;
    for (const auto& f : logFiles) {
        logger.addLog(f);
    }
    if (!initialMessage.empty()) {
        logger.log(initialMessage);
    }
    return logger;
}

int main() {
    std::cout << "=== DEMO Item 13: Logger cu unique_ptr ===\n";

    std::vector<std::string> files1 = {"system.log", "debug.log"};
    Logger systemLogger = createCustomLogger(files1, "System logger initialized");
    systemLogger.log("System is running normally");

    std::vector<std::string> files2 = {"errors.log"};
    Logger errorLogger = createCustomLogger(files2, "Error logger initialized");
    errorLogger.log("First error message");

    std::cout << "\n=== DEMO TimeStampedLogFile ===\n";
    TimeStampedLogFile tlog("timestamped.log", true);
    tlog.write("System start with timestamp");
    tlog.write("Another message");

    // Move demo
    Logger movedLogger = std::move(systemLogger);
    movedLogger.log("Message after move");

    // -------------------------
    // THREAD DEMOS
    // -------------------------
    runUnsafeDemoDual();  // DEMO DOAR CU THREAD-URI NESINCRONIZATE
    runSafeDemo();        // DEMO SINCRONIZAT CU MUTEX

    std::cout << "\n=== Sfarsit demo ===\n";
    return 0;
}
