#pragma once

#include <map>
#include <string>
#include <memory>

namespace Zelinf {
namespace PolyCalc {

namespace Service {
class Polynomial;
}

namespace App {

class Executor;

// interface
class Evaluator {
public:
    explicit Evaluator(Executor &executor) : executor(executor) {}

    virtual std::string evaluate(const std::string &) = 0;

protected:
    Executor &executor;
};

}
}
}
