#include "Logger.hpp"
#include <utility>

int main() {
    std::cout << "=== Logger Demo Start ===\n";

    Logger log1;
    log1.addLog("log1.txt");
    log1.addLog("log2.txt");
    log1.log("Initial log message.");

    // copy constr usage
    Logger log2 = log1;
    log2.log("Message from copied logger.");

    // move constr usage
    Logger log3 = std::move(log1);
    log3.log("Message from moved logger.");

    std::cout << "=== Logger Demo End ===\n";
    return 0;
}
