#include "BiOperator.h"
#include "Plus.h"
#include "Minus.h"
#include "Multiply.h"
#include "Derivation.h"
#include "Power.h"

namespace Zelinf {
namespace PolyCalc {
namespace App {
namespace Expression {
namespace Operators {

const std::vector<std::shared_ptr<BiOperator>> BiOperator::defaultOperators(
        {
                std::make_shared<Plus>(),
                std::make_shared<Minus>(),
                std::make_shared<Multiply>(),
                std::make_shared<Derivation>(),
                std::make_shared<Power>()
        }
);

BiOperator::~BiOperator() {

}

}
}
}
}
}
