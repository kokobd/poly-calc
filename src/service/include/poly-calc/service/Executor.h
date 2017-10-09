#pragma once

#include <memory>
#include <vector>
#include <map>

namespace Zelinf {
namespace PolyCalc {
namespace Service {

namespace Poly {
class Polynomial;
}

class Command;

class Evaluator;

/**
 * The main executor. An executor holds a vector of Command, and an evaluator.
 * The main functionality of an executor is implemented in the 'execute' method.
 * See documentations of 'execute' and 'Command' for more information.
 */
class Executor {
private:
    std::map<std::string, std::shared_ptr<Poly::Polynomial>> storedPolys;
public:
    /**
     * Constructs the default executor. This is the only way to
     * obtain an object of Executor.
     */
    Executor();

    /**
     * Parses and executes the input string.
     * Input starts with an english colon, i.e. ':', will be treated as commands. If
     * a command of matching name is registered, that command will get executed.
     * Input not starts with an english colon will be treated as an expression ans get passed
     * to the evaluator.
     * @param input the input string
     * @return The result.
     * @throws std::exception possibly thrown by commands and the evaluator.
     */
    std::string execute(const std::string &input);

    /**
     * Get a view of the currently registered commands.
     * @return a const reference to the commands.
     */
    const std::vector<std::shared_ptr<Command>> &getCommands() const {
        return commands;
    }

    /**
     * Get a reference to the stored polynomials. It could be used to
     * modify the stored polynomials.
     * @return A map from polynomial identifiers to shared_ptr of polynomials.
     */
    decltype(storedPolys) &getStoredPolys() { return storedPolys; }

    /**
     * Get a const reference to the stored polynomials.
     * @return A const map from polynomial identifiers to shared_ptr of polynomials.
     */
    const decltype(storedPolys) &getStoredPolys() const { return storedPolys; }

private:
    std::vector<std::shared_ptr<Command>> commands;

    std::shared_ptr<Evaluator> evaluator;

    void config();
};

}
}
}