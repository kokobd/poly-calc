#pragma once

#include "../Command.h"
#include <stdexcept>

namespace Zelinf {
namespace PolyCalc {
namespace App {
namespace Commands {

class QuitExcept : public std::exception {
    const char *what() const noexcept override {
        return "Exiting the program.";
    }
};

class Quit : public Command {
public:
    std::vector<std::string> names() const override {
        return {"quit", "q"};
    }

    std::string run(std::vector<std::string> args) override;
};

}
}
}
}
