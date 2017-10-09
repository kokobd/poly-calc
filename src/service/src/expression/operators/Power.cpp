#include <poly-calc/service/expression/operators/Power.h>
#include <poly-calc/service/poly/Polynomial.h>

namespace Zelinf {
namespace PolyCalc {
namespace Service {
namespace Expression {
namespace Operators {

std::shared_ptr<Poly::Polynomial>
Power::apply(std::shared_ptr<Poly::Polynomial> lhs,
             std::shared_ptr<Poly::Polynomial> rhs) {
    if (lhs == nullptr || rhs == nullptr) {
        throw std::invalid_argument("NullPointerException");
    }
    if (!rhs->isConstant()) {
        throw std::invalid_argument("Right-hand operand for '^' must be constant");
    }
    return std::make_shared<Poly::Polynomial>(lhs->power(rhs->evaluate(0)));
}
}
}
}
}
}
