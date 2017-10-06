#pragma once

#include <memory>
#include <vector>
#include <map>

namespace Zelinf {
namespace PolyCalc {

namespace Service {
class Polynomial;
}

namespace App {

class Command;

class Evaluator;

class Executor {
public:
    Executor();

    std::string execute(const std::string &input);

    const std::vector<std::shared_ptr<Command>> getCommands() const {
        return commands;
    }

private:
    std::vector<std::shared_ptr<Command>> commands;

    std::shared_ptr<Evaluator> evaluator;

    std::map<std::string, std::shared_ptr<Service::Polynomial>> storedPolys;

    void config();
};

}
}
}