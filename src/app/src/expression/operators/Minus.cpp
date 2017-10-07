#include "Minus.h"

#include <poly-calc/service/Polynomial.h>

namespace Zelinf {
namespace PolyCalc {
namespace App {
namespace Expression {
namespace Operators {


std::shared_ptr<Service::Polynomial>
Minus::apply(std::shared_ptr<Service::Polynomial> lhs,
             std::shared_ptr<Service::Polynomial> rhs) {
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
