#include "BiOperator.h"
#include "Plus.h"
#include "Minus.h"
#include "Multiply.h"
#include "Derivation.h"

namespace Zelinf {
namespace PolyCalc {
namespace App {
namespace Expression {
namespace Operators {

std::vector<std::shared_ptr<BiOperator>> BiOperator::defaultOperators(
        {
                std::make_shared<Plus>(),
                std::make_shared<Minus>(),
                std::make_shared<Multiply>()
        }
);

}
}
}
}
}
