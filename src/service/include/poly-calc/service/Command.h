#pragma once

#include <vector>
#include <string>

namespace Zelinf {
namespace PolyCalc {
namespace Service {

class Executor;

/**
 * The Command abstract class. Any command should extends the class
 * and implement the pure virtual methods. As we have no reflection for
 * now, don't forget to add your class to the private 'config()' method
 * of Executor.
 */
class Command {
public:
    /**
     * Constructs a Command. Subclasses should call this constructor
     * from their own.
     * @param executor A reference to the enclosing executor.
     */
    explicit Command(Executor &executor) : executor(executor) {}

    /**
     * Names of the command. Such as {"help", "h"}
     * @return a vector of command names.
     */
    virtual std::vector<std::string> names() const = 0;

    /**
     * Runs the command. This is the core function for subclasses to
     * implement.
     * @param args Arguments to the command.
     * @return The result.
     */
    virtual std::string run(std::vector<std::string> args) = 0;

    /**
     * Some help information of this command.
     * @return the help information.
     */
    virtual std::string helpInfo() const = 0;

    /**
     * Every abstract class should have a virtual destructor.
     */
    virtual ~Command() = 0;

protected:
    Executor &executor;
};

}
}
}
