#pragma once

#include "poly-calc/service/expression/BiOperator.h"

namespace Zelinf {
namespace PolyCalc {
namespace Service {
namespace Expression {
namespace Operators {

class Minus : public BiOperator {
public:
    int64_t precedence() const override {
        return 1;
    }

    bool leftAssoc() const override {
        return true;
    }

    char symbol() const override {
        return '-';
    }

    std::shared_ptr<Poly::Polynomial>
    apply(std::shared_ptr<Poly::Polynomial> lhs, std::shared_ptr<Poly::Polynomial> rhs) override;

    ~Minus() override = default;
};

}
}
}
}
}
