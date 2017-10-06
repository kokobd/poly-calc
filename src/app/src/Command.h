#pragma once

#include <vector>
#include <string>

// interface
class Command {
public:
    virtual std::vector<std::string> names() const = 0;

    virtual std::string run(std::vector<std::string> args) = 0;
};
