#pragma once

#include <memory>
#include "../Evaluator.h"
#include <poly-calc/service/Polynomial.h>

namespace Zelinf {
namespace PolyCalc {
namespace App {
namespace Expression {

class SimpleEvaluator : public Evaluator {
public:
    explicit SimpleEvaluator(Executor &executor) : Evaluator(executor) {}

    std::string evaluate(const std::string &input) override;

private:
    std::shared_ptr<Service::Polynomial> parse(const std::string &str);
};

}


}
}
}
