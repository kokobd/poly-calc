#include <poly-calc/service/Monomial.h>
#include <stdexcept>
#include <fmt/format.h>
#include <cmath>

namespace Zelinf {
namespace PolyCalc {
namespace Service {

std::int64_t Monomial::evaluate(int64_t var) const noexcept {
    int result = 1;
    int64_t exp = exponent;
    while (exp != 0) {
        if ((exp & 1) != 0)
            result *= var;
        exp >>= 1;
        var *= var;
    }
    result *= coefficient;
    return result;
}

Monomial::Monomial(std::int64_t coefficient, std::int64_t exponent)
        : coefficient(coefficient), exponent(exponent) {
    if (exponent < 0) {
        throw std::invalid_argument(
                "Exponent of monomials can not be negative.");
    }
    simplify();
}

Monomial &Monomial::operator*=(const Monomial &rhs) noexcept {
    coefficient *= rhs.coefficient;
    exponent += rhs.exponent;
    simplify();

    return *this;
}

std::string Monomial::show(bool showPosSign, bool showZero) const noexcept {
    std::string result;
    if (showPosSign || coefficient < 0) {
        result += coefficient >= 0 ? '+' : '-';
    }

    int64_t coef_abs = std::abs(coefficient);
    if (showZero || coefficient != 0) {
        if (coef_abs != 1 || isConstant()) {
            result += std::to_string(coef_abs);
        }
    }

    if (!isConstant()) {
        result += 'x';
        if (exponent != 1) {
            result += fmt::format("^{}", exponent);
        }
    }
    return result;
}

Monomial &Monomial::operator+=(const Monomial &rhs) {
    if (coefficient == 0) {
        *this = rhs;
    } else if (rhs.coefficient == 0) {
        return *this;
    } else {
        if (exponent != rhs.exponent) {
            throw std::invalid_argument("Monomials with different exponent can't be added together");
        }
        coefficient += rhs.coefficient;
        simplify();
    }

    return *this;
}

Monomial operator*(const Monomial &lhs, const Monomial &rhs) noexcept {
    Monomial result = lhs;
    result *= rhs;
    return result;
}

Monomial operator+(const Monomial &lhs, const Monomial &rhs) {
    Monomial result = lhs;
    result += rhs;
    return result;
}

Monomial &Monomial::derivation(int64_t times) noexcept {
    if (times <= 0) {
        return *this;
    }
    if (times > exponent) {
        coefficient = 0;
        exponent = 0;
        return *this;
    }

    for (int64_t i = 0; i < times; i++) {
        coefficient *= (exponent - i);
    }
    exponent -= times;
    return *this;
}

}
}
}
