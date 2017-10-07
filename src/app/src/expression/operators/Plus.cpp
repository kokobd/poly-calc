#include <poly-calc/service/Polynomial.h>
#include "Plus.h"
#include <stdexcept>

namespace Zelinf {
namespace PolyCalc {
namespace App {
namespace Expression {
namespace Operators {

std::shared_ptr<Service::Polynomial>
Plus::apply(std::shared_ptr<Service::Polynomial> lhs,
            std::shared_ptr<Service::Polynomial> rhs) {
    if (lhs == nullptr || rhs == nullptr) {
        throw std::invalid_argument("NullPointerException");
    }

    lhs->operator+=(*rhs);
    return lhs;
}

}
}
}
}
}
