#pragma once

#include <map>
#include <string>
#include <memory>

namespace Zelinf {
namespace PolyCalc {

namespace Service {
class Polynomial;
}

namespace App {

// interface
class Evaluator {
public:
    virtual void setStoredPolys(std::map<std::string, std::shared_ptr<Service::Polynomial>> &) = 0;

    virtual std::string evaluate(const std::string &) = 0;
};

}
}
}
