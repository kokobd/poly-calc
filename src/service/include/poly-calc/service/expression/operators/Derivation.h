#pragma once

#include "poly-calc/service/expression/BiOperator.h"

namespace Zelinf {
namespace PolyCalc {
namespace Service {
namespace Expression {
namespace Operators {

class Derivation : public BiOperator {
public:
    int64_t precedence() const override {
        return 4;
    }

    bool leftAssoc() const override {
        return true;
    }

    char symbol() const override {
        return '\'';
    }

    std::shared_ptr<Poly::Polynomial>
    apply(std::shared_ptr<Poly::Polynomial> lhs, std::shared_ptr<Poly::Polynomial> rhs) override;

    ~Derivation() override = default;
};

}
}
}
}
}
