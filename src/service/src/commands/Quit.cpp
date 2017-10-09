#include <poly-calc/service/commands/Quit.h>

namespace Zelinf {
namespace PolyCalc {
namespace Service {
namespace Commands {

std::string Quit::run(std::vector<std::string> args) {
    throw QuitExcept();
}

std::string Quit::helpInfo() const {
    return "Exits the program.";
}

}
}
}
}
