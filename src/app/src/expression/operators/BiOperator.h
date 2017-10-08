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
    virtual int64_t precedence() const = 0;

    virtual bool leftAssoc() const = 0;

    virtual char symbol() const = 0;

    virtual std::shared_ptr<Service::Polynomial> apply(
            std::shared_ptr<Service::Polynomial> lhs,
            std::shared_ptr<Service::Polynomial> rhs) = 0;

    virtual ~BiOperator() = 0;

    static const std::vector<std::shared_ptr<BiOperator>> defaultOperators;
};
}

}
}
}
}
