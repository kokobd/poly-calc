#include "Derivation.h"
#include <poly-calc/service/Polynomial.h>
#include "../ParseError.h"

namespace Zelinf {
namespace PolyCalc {
namespace App {
namespace Expression {
namespace Operators {


std::shared_ptr<Service::Polynomial>
Derivation::apply(std::shared_ptr<Service::Polynomial> lhs,
                  std::shared_ptr<Service::Polynomial> rhs) {
    if (lhs == nullptr || rhs == nullptr) {
        throw std::invalid_argument("NullPointerException");
    }

    if (!rhs->isConstant()) {
        throw ParseError("The second argument of ' can not be non-constant");
    } else {
        std::shared_ptr<Service::Polynomial> result = std::make_shared<Service::Polynomial>(*lhs);
        result->derivation(rhs->evaluate(0));
        return result;
    }
}

}
}
}
}
}
