#pragma once

#include <memory>
#include <vector>

namespace Zelinf {
namespace PolyCalc {

namespace Service {
class Polynomial;
}

namespace App {
namespace Expression {
namespace Operators {

class BiOperator {
public:
    virtual int64_t precedence() = 0;

    virtual bool leftAssoc() = 0;

    virtual std::shared_ptr<Service::Polynomial> apply(
            std::shared_ptr<Service::Polynomial> lhs,
            std::shared_ptr<Service::Polynomial> rhs) = 0;

    static std::vector<std::shared_ptr<BiOperator>> defaultOperators;
};
}

}
}
}
}
