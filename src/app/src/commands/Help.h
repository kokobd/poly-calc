#pragma once

#include "../Command.h"

namespace Zelinf {
namespace PolyCalc {
namespace App {
namespace Commands {

class Help : public Command {
public:
    explicit Help(Executor &executor) : Command(executor) {}

    std::vector<std::string> names() const override;

    std::string run(std::vector<std::string> args) override;

    std::string helpInfo() const override;
};

}
}
}
}
