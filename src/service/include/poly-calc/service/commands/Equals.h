#pragma once

#include <memory>
#include "poly-calc/service/Command.h"

namespace Zelinf {
namespace PolyCalc {
namespace Service {

namespace Poly {
class Polynomial;
}

namespace Commands {

class Equals : public Command {
public:
    explicit Equals(Executor &executor);

    std::vector<std::string> names() const override {
        return {"equals", "eq"};
    }

    std::string helpInfo() const override {
        return "'equals p q' determines whether p equals q";
    }

    std::string run(std::vector<std::string> args) override;

    ~Equals() override = default;

private:
    std::shared_ptr<Poly::Polynomial> findPolyWithName(const std::string &name) const;
};

}
}
}
}
