#include <poly-calc/service/expression/operators/Minus.h>

#include <poly-calc/service/poly/Polynomial.h>

namespace Zelinf {
namespace PolyCalc {
namespace Service {
namespace Expression {
namespace Operators {


std::shared_ptr<Poly::Polynomial>
Minus::apply(std::shared_ptr<Poly::Polynomial> lhs,
             std::shared_ptr<Poly::Polynomial> rhs) {
    if (lhs == nullptr || rhs == nullptr) {
        throw std::invalid_argument("NullPointerException");
    }

    lhs->operator-=(*rhs);
    return lhs;
}

}
}
}
}
}
