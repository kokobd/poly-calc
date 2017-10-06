#include "Executor.h"
#include <sstream>
#include <algorithm>
#include <fmt/format.h>
#include "Evaluator.h"

#include "commands/Quit.h"
#include "commands/Help.h"

namespace Zelinf {
namespace PolyCalc {
namespace App {

std::string Executor::execute(const std::string &input) {
    if (input[0] == ':') {
        std::istringstream is(input.substr(1));

        std::string cmd_name;
        is >> cmd_name;
        // Lookup command name, if found, execute it.
        auto cmd_it = std::find_if(commands.cbegin(), commands.cend(), [&cmd_name](const std::shared_ptr<Command> cmd) {
            std::vector<std::string> names = cmd->names();
            return std::find(names.cbegin(), names.cend(), cmd_name) != names.cend();
        });
        if (cmd_it != commands.cend()) {
            std::vector<std::string> args;
            std::string arg;
            while (is >> arg) {
                args.push_back(arg);
            }
            return (*cmd_it)->run(args);
        }
        return fmt::format("Command '{}' not found.", cmd_name);

    }

    return evaluator->evaluate(input);
}

Executor::Executor() {
    config();
}

/**
 * This function adds all classes in 'commands' sub-folder
 * to commands, choose a default implementation of Evaluator
 * from sub-folder 'expression'.
 */
void Executor::config() {
    commands = {
            std::make_shared<Commands::Quit>(*this),
            std::make_shared<Commands::Help>(*this)
    };
}

}
}
}
