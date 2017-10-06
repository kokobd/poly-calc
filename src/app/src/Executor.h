#pragma once

#include <memory>
#include <vector>
#include <map>
#include "Command.h"
#include "Evaluator.h"

namespace Zelinf {
namespace PolyCalc {

namespace Service {
class Polynomial;
}

namespace App {

class Executor {
public:
    Executor();
    std::string execute(const std::string &input);

private:
    std::vector<std::shared_ptr<Command>> commands;

    std::shared_ptr<Evaluator> evaluator;

    std::map<std::string, std::shared_ptr<Service::Polynomial>> storedPolys;

    void config();
};

}
}
}