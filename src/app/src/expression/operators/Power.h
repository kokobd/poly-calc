#pragma once

#include "BiOperator.h"

namespace Zelinf {
namespace PolyCalc {
namespace App {
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

    std::shared_ptr<Service::Polynomial>
    apply(std::shared_ptr<Service::Polynomial> lhs, std::shared_ptr<Service::Polynomial> rhs) override;
};

}
}
}
}
}
