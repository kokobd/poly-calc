#pragma once

#include <set>
#include "Monomial.h"
#include <functional>
#include <initializer_list>

namespace Zelinf {
namespace PolyCalc {
namespace Service {
namespace Poly {

/**
 * Represents a simplified polynomial.
 * Note that the polynomial always contains at least one monomial, zero.
 */
class Polynomial {
public:
    /**
     * Construct the zero polynomial.
     */
    Polynomial() noexcept;

    /**
     * Construct a polynomial with an initializer_list of monomials.
     * Example: <code>Polynomial p({{1, 2}, {3})</code>
     * @param initMonos an initializer_list of monomials.
     */
    Polynomial(std::initializer_list<Monomial> initMonos);

    /**
     * Convert the polynomial to a std::string. The string contains
     * no whitespaces.
     * @return  the generated string.
     */
    std::string show() const noexcept;

    /**
     * Adds another polynomial to *this.
     * @param rhs the right-hand symbol.
     * @return a reference to *this
     */
    Polynomial &operator+=(const Polynomial &rhs) noexcept;

    /**
     * Adds two polynomials together.
     * @param lhs The left-hand symbol.
     * @param rhs The right-hand symbol.
     * @return A new polynomial represents the result.
     */
    friend Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs) noexcept;

    /**
     * Substract another polynomial from the current one.
     * @param rhs The right-hand symbol.
     * @return A reference to *this.
     */
    Polynomial &operator-=(const Polynomial &rhs) noexcept;

    /**
     * Substracts two polynomials.
     * @param lhs The left-hand symbol.
     * @param rhs The right-hand symbol.
     * @return A new polynomial represents the result.
     */
    friend Polynomial operator-(const Polynomial &lhs, const Polynomial &rhs) noexcept;

    /**
     * Multiplies *this and rhs.
     * @param rhs The right-hand symbol.
     * @return A reference to *this.
     */
    Polynomial &operator*=(const Polynomial &rhs) noexcept;

    /**
     * Multiplies two polynomials.
     * @param lhs The left-hand symbol.
     * @param rhs The right-hand symbol.
     * @return A new polynomial represents the result.
     */
    friend Polynomial operator*(const Polynomial &lhs, const Polynomial &rhs) noexcept;

    /**
     * Determines whether two polynomials are equal.
     * @param lhs The left-hand symbol.
     * @param rhs The right-hand symbol.
     * @return Whether lhs equals rhs.
     */
    friend bool operator==(const Polynomial &lhs, const Polynomial &rhs) noexcept {
        return lhs.monos == rhs.monos;
    }

    /**
     * Computes the derivation. The result is stored in
     * *this.
     * @param times The derivation order.
     * @return A reference to *this.
     */
    Polynomial &derivation(int64_t times) noexcept;

    /**
     * Computes the power with given exponent.
     * Complexity: O(logN), where N is the exponent.
     * @param exponent The exponent. (Must be constant)
     * @throws std::invalid_argument if exponent is not a constant,
     * or, is negative.
     * @return The power.
     */
    Polynomial power(int64_t exponent) const;

    /**
     * Evaluates the polynomial. Substitute the variable with
     * the given value.
     * @param var The value to substitute.
     * @return The value of the whole polynomial.
     */
    int64_t evaluate(int64_t var) const noexcept;

    /**
     * Determines whether the polynomial is a constant.
     * @return true if the polynomial is a constant.
     */
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
}
