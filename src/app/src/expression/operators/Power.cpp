#include "Power.h"
#include <poly-calc/service/Polynomial.h>

namespace Zelinf {
namespace PolyCalc {
namespace App {
namespace Expression {
namespace Operators {

std::shared_ptr<Service::Polynomial>
Power::apply(std::shared_ptr<Service::Polynomial> lhs,
             std::shared_ptr<Service::Polynomial> rhs) {
    if (lhs == nullptr || rhs == nullptr) {
        throw std::invalid_argument("NullPointerException");
    }
    if (!rhs->isConstant()) {
        throw std::invalid_argument("Right-hand operand for '^' must be constant");
    }
    return std::make_shared<Service::Polynomial>(lhs->power(rhs->evaluate(0)));
}
}
}
}
}
}
