#pragma once

#include "BiOperator.h"

namespace Zelinf {
namespace PolyCalc {
namespace App {
namespace Expression {
namespace Operators {

class Multiply : public BiOperator {
public:
    int64_t precedence() const override {
        return 2;
    }

    bool leftAssoc() const override {
        return true;
    }

    char symbol() const override {
        return '*';
    }

    std::shared_ptr<Service::Polynomial>
    apply(std::shared_ptr<Service::Polynomial> lhs, std::shared_ptr<Service::Polynomial> rhs) override;

    ~Multiply() override = default;
};

}
}
}
}
}
