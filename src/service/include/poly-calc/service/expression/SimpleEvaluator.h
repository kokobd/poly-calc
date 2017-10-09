#pragma once

#include <memory>
#include "poly-calc/service/Evaluator.h"
#include <poly-calc/service/poly/Polynomial.h>

namespace Zelinf {
namespace PolyCalc {
namespace Service {
namespace Expression {

class SimpleEvaluator : public Evaluator {
public:
    explicit SimpleEvaluator(Executor &executor) : Evaluator(executor) {}

    std::string evaluate(const std::string &input) override;

    std::string helpInfo() override;

private:
    std::shared_ptr<Poly::Polynomial> parse(const std::string &str);

};

}


}
}
}
