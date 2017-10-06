#include <iostream>
#include "Executor.h"

int main() {
    using namespace Zelinf::PolyCalc::App;

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