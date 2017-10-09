#include <poly-calc/service/expression/operators/Derivation.h>
#include <poly-calc/service/poly/Polynomial.h>
#include <poly-calc/service/expression/ParseError.h>

namespace Zelinf {
namespace PolyCalc {
namespace Service {
namespace Expression {
namespace Operators {


std::shared_ptr<Poly::Polynomial>
Derivation::apply(std::shared_ptr<Poly::Polynomial> lhs,
                  std::shared_ptr<Poly::Polynomial> rhs) {
    if (lhs == nullptr || rhs == nullptr) {
        throw std::invalid_argument("NullPointerException");
    }

    if (!rhs->isConstant() || rhs->evaluate(0) < 0) {
        throw ParseError("The second argument of must be non-negative constant");
    } else {
        std::shared_ptr<Poly::Polynomial> result = std::make_shared<Poly::Polynomial>(*lhs);
        result->derivation(rhs->evaluate(0));
        return result;
    }
}

}
}
}
}
}
