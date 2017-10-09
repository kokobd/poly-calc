#pragma once

#include "poly-calc/service/expression/BiOperator.h"

namespace Zelinf {
namespace PolyCalc {
namespace Service {
namespace Expression {
namespace Operators {

class Power : public BiOperator {
public:
    int64_t precedence() const override {
        return 3;
    }

    bool leftAssoc() const override {
        return false;
    }

    char symbol() const override {
        return '^';
    }

    ~Power() override = default;

    std::shared_ptr<Poly::Polynomial>
    apply(std::shared_ptr<Poly::Polynomial> lhs, std::shared_ptr<Poly::Polynomial> rhs) override;
};

}
}
}
}
}
