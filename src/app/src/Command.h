#pragma once

#include <vector>
#include <string>

namespace Zelinf {
namespace PolyCalc {
namespace App {

class Executor;

class Command {
public:
    explicit Command(Executor &executor) : executor(executor) {}

    virtual std::vector<std::string> names() const = 0;

    virtual std::string run(std::vector<std::string> args) = 0;

    virtual std::string helpInfo() const = 0;

    virtual ~Command() = 0;

protected:
    Executor &executor;
};

}
}
}
