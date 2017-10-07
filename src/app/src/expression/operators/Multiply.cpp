#include "Multiply.h"
#include <poly-calc/service/Polynomial.h>

namespace Zelinf {
namespace PolyCalc {
namespace App {
namespace Expression {
namespace Operators {


std::shared_ptr<Service::Polynomial>
Multiply::apply(std::shared_ptr<Service::Polynomial> lhs,
                std::shared_ptr<Service::Polynomial> rhs) {
    if (lhs == nullptr || rhs == nullptr) {
        throw std::invalid_argument("NullPointerException");
    }
    // (*lhs * *rhs) is a rvalue, thus move constructor is called,
    // actual data won't be copied.
    return std::make_shared<Service::Polynomial>(*lhs * (*rhs));
}
}
}
}
}
}
