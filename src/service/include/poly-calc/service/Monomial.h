#pragma once

#include <cstdint>
#include <string>

namespace Zelinf {
namespace PolyCalc {
namespace Service {

class Monomial {
public:
    Monomial(int64_t coefficient = 0,
             int64_t exponent = 0);

    Monomial &operator*=(const Monomial &rhs) noexcept;

    friend Monomial operator*(const Monomial &lhs, const Monomial &rhs) noexcept;

    friend bool operator==(const Monomial &lhs, const Monomial &rhs) noexcept {
        return lhs.coefficient == rhs.coefficient
               && lhs.exponent == rhs.exponent;
    }

    /**
     * Determine whether the monomial is constant.
     * @return whether the monomial is constant.
     */
    bool isConstant() const noexcept {
        return exponent == 0;
    }

    std::int64_t evaluate(int64_t var) const noexcept;

    std::string show(bool showPosSign, bool showZero = false) const noexcept;

    int64_t getCoefficient() const noexcept { return coefficient; }

    int64_t getExponent() const noexcept { return exponent; }

    Monomial &operator+=(const Monomial &rhs);

    friend Monomial operator+(const Monomial &lhs, const Monomial &rhs);

    Monomial &derivation(int64_t times) noexcept;

    Monomial &negate() noexcept {
        coefficient = -coefficient;
        return *this;
    }

private:
    std::int64_t coefficient{0};
    std::int64_t exponent{0};

    /**
     * Simplify the monomial. That is, convert 0*x^N to 0*x^0
     */
    void simplify() {
        if (coefficient == 0) {
            exponent = 0;
        }
    }
};

}
}
}

