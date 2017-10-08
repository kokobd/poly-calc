#pragma once

#include <set>
#include "Monomial.h"
#include <functional>
#include <initializer_list>

namespace Zelinf {
namespace PolyCalc {
namespace Service {

class Polynomial {
public:
    Polynomial() noexcept;

    Polynomial(std::initializer_list<Monomial> initMonos);

    std::string show() const noexcept;

    Polynomial &operator+=(const Polynomial &rhs) noexcept;

    friend Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs) noexcept;

    Polynomial &operator-=(const Polynomial &rhs) noexcept;

    friend Polynomial operator-(const Polynomial &lhs, const Polynomial &rhs) noexcept;

    Polynomial &operator*=(const Polynomial &rhs) noexcept;

    friend Polynomial operator*(const Polynomial &lhs, const Polynomial &rhs) noexcept;

    friend bool operator==(const Polynomial &lhs, const Polynomial &rhs) noexcept {
        return lhs.monos == rhs.monos;
    }

    Polynomial &derivation(int64_t times) noexcept;

    Polynomial power(int64_t exponent) const;

    int64_t evaluate(int64_t var) const noexcept;

    bool isConstant() const noexcept {
        return monos.size() == 1 && monos.cbegin()->isConstant();
    }

private:
    static std::function<bool(const Monomial &lhs, const Monomial &rhs)> mono_cmp;

    std::set<Monomial, decltype(mono_cmp)> monos;

    bool isZero() const noexcept {
        return monos.size() == 1 && monos.begin()->getCoefficient() == 0;
    }
};

}
}
}
