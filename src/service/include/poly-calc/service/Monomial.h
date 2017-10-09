#pragma once

#include <cstdint>
#include <string>

namespace Zelinf {
namespace PolyCalc {
namespace Service {

/**
 * Represents a monomial, such as 3x^5.
 * Coefficients and exponents are int64_t, NOTE THAT
 * no overflow check is performed.
 * The monomial will be automatically simplified. 0*x^n
 * becomes 0.
 */
class Monomial {
public:
	/**
	 * Construct a Monomial with specified coefficient and exponent.
	 * If the exponent is zero, the monomial becomes a constant.
	 * @throws std::invalid_argument if exponent is negative.
	 */
    Monomial(int64_t coefficient = 0,
             int64_t exponent = 0);

	/**
	 * Multiplies *this with another monomial.
	 * Returns a reference to the current object.
	 */
    Monomial &operator*=(const Monomial &rhs) noexcept;

	/**
	 * Multiplies two monomials.
	 * Returns a new Monomial object.
	 */
    friend Monomial operator*(const Monomial &lhs, const Monomial &rhs) noexcept;

	/**
	 * Determine whether two Monomials are equal.
	 */
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

	/**
	 * Substitute the variable with given value, returns the result.
	 */
    std::int64_t evaluate(int64_t var) const noexcept;

	/**
	 * Convert the monomial to std::string.
	 * @param showPosSign show the '+' sign if showPosSign is true and
	 * the coefficient is non-negative.
	 */
    std::string show(bool showPosSign, bool showZero = false) const noexcept;

	/**
	 * Get the coefficient.
	 * @returns the coefficient.
	 */
    int64_t getCoefficient() const noexcept { return coefficient; }

	/**
	 * Get the exponent.
	 * @returns the exponent.
	 */
    int64_t getExponent() const noexcept { return exponent; }

	/**
	 * Adds another monomial to *this.
	 * @returns a reference to *this
	 */
    Monomial &operator+=(const Monomial &rhs);

	/**
	 * Adds two monomial together.
	 * @returns a new monomial represents the sum.
	 */
    friend Monomial operator+(const Monomial &lhs, const Monomial &rhs);

	/**
	 * Calculates the n'th order derivation. The result is stored
	 * directly in *this.
	 * @param the derivation order.
	 * @returns a reference to *this.
	 */
    Monomial &derivation(int64_t times) noexcept;

	/**
	 * Negates the current monomial.
	 * @returns a reference to *this.
	 */
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

