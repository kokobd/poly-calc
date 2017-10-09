#include <iostream>
#include <string>
#include "poly-calc/service/Executor.h"

int main() {
    using namespace Zelinf::PolyCalc::Service;

    Executor exec;

    std::string line;
    while (true) {
        try {
            std::cout << "calc> ";
            std::getline(std::cin, line);
            std::cout << exec.execute(line) << std::endl;
        } catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
            break;
        }
    }
    return 0;
}