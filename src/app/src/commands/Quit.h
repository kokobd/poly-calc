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
    explicit Quit(Executor &executor) : Command(executor) {}

    std::vector<std::string> names() const override {
        return {"quit", "q"};
    }

    std::string run(std::vector<std::string> args) override;

    std::string helpInfo() const override;

    ~Quit() override = default;
};

}
}
}
}
