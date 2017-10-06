#include "Quit.h"

namespace Zelinf {
namespace PolyCalc {
namespace App {
namespace Commands {

std::string Quit::run(std::vector<std::string> args) {
    throw QuitExcept();
}

}
}
}
}
