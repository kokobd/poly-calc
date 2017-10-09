#include <poly-calc/service/commands/Equals.h>
#include <poly-calc/service/Executor.h>
#include <fmt/format.h>
#include <poly-calc/service/poly/Polynomial.h>

namespace Zelinf {
namespace PolyCalc {
namespace Service {
namespace Commands {


Equals::Equals(Executor &executor) : Command(executor) {}

std::string Equals::run(std::vector<std::string> args) {
    if (args.empty()) {
        return "'equals' should be called with at least one argument.";
    }

    auto p = findPolyWithName(args[0]);
    if (p == nullptr) {
        return fmt::format("'{}' could not be found.", args[0]);
    }
    for (const std::string &name : args) {
        auto q = findPolyWithName(name);
        if (q == nullptr) {
            return fmt::format("'{}' could not be found.", name);
        }
        if (*p != *q) {
            return "Not equal";
        }
    }

    return "Equal";
}

std::shared_ptr<Poly::Polynomial> Equals::findPolyWithName(const std::string &name) const {
    auto it = executor.getStoredPolys().find(name);
    if (it == executor.getStoredPolys().cend()) {
        return nullptr;
    }
    return it->second;
}

}
}
}
}
