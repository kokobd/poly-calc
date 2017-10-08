#pragma once

#include "BiOperator.h"

namespace Zelinf {
namespace PolyCalc {
namespace App {
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

    std::shared_ptr<Service::Polynomial>
    apply(std::shared_ptr<Service::Polynomial> lhs, std::shared_ptr<Service::Polynomial> rhs) override;

    ~Derivation() override = default;
};

}
}
}
}
}
