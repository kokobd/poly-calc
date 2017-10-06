#include "Show.h"
#include "../Executor.h"
#include <sstream>
#include <poly-calc/service/Polynomial.h>
#include <fmt/format.h>

namespace Zelinf {
namespace PolyCalc {
namespace App {
namespace Commands {


std::vector<std::string> Show::names() const {
    return {"show"};
}

std::string Show::run(std::vector<std::string> args) {
    std::ostringstream os;
    if (args.empty()) { // show all statements
        for (const auto &p : executor.getStoredPolys()) {
            os << p.first << " = " << p.second->show() << '\n';
        }
    } else {
        for (const std::string &statement_name : args) {
            auto it = executor.getStoredPolys().find(statement_name);
            if (it == executor.getStoredPolys().cend()) {
                os << fmt::format("'{}' doesn't exist.\n", statement_name);
            } else {
                os << it->first << " = " << it->second->show() << '\n';
            }
        }
    }
    return os.str();
}

std::string Show::helpInfo() const {
    return "'show p q r ...' shows p q r if they are stored. Shows all"
            "stored expressions if no arguments are given.";
}
}
}
}
}
