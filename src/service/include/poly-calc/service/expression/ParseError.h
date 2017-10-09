#pragma once

#include <stdexcept>

namespace Zelinf {
namespace PolyCalc {
namespace Service {
namespace Expression {

class ParseError : public std::runtime_error {
public:
    explicit ParseError(const std::string &what) : std::runtime_error(what) {}
};

}
}
}
}