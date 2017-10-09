#include <poly-calc/service/expression/BiOperator.h>
#include <poly-calc/service/expression/operators/Plus.h>
#include <poly-calc/service/expression/operators/Minus.h>
#include <poly-calc/service/expression/operators/Multiply.h>
#include <poly-calc/service/expression/operators/Derivation.h>
#include <poly-calc/service/expression/operators/Power.h>

namespace Zelinf {
namespace PolyCalc {
namespace Service {
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
