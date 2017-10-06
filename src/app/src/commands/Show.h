#pragma once

#include "../Command.h"

namespace Zelinf {
namespace PolyCalc {
namespace App {
namespace Commands {

class Show : public Command {
public:
    Show(Executor &executor) : Command(executor) {}

    std::vector<std::string> names() const override;

    std::string run(std::vector<std::string> args) override;

    std::string helpInfo() const override;
};

}
}
}
}

