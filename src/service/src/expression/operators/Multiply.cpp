#include <poly-calc/service/expression/operators/Multiply.h>
#include <poly-calc/service/poly/Polynomial.h>

namespace Zelinf {
namespace PolyCalc {
namespace Service {
namespace Expression {
namespace Operators {


std::shared_ptr<Poly::Polynomial>
Multiply::apply(std::shared_ptr<Poly::Polynomial> lhs,
                std::shared_ptr<Poly::Polynomial> rhs) {
    if (lhs == nullptr || rhs == nullptr) {
        throw std::invalid_argument("NullPointerException");
    }
    // (*lhs * *rhs) is a rvalue, thus move constructor is called,
    // actual data won't be copied.
    return std::make_shared<Poly::Polynomial>(*lhs * (*rhs));
}
}
}
}
}
}
