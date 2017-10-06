#include <poly-calc/service/Polynomial.h>

namespace Zelinf {
namespace PolyCalc {
namespace Service {

std::function<bool(const Monomial &lhs, const Monomial &rhs)> Polynomial::mono_cmp(
        [](const Monomial &lhs, const Monomial &rhs) -> bool {
            return lhs.getExponent() > rhs.getExponent();
        });

Polynomial::Polynomial() noexcept
        : monos(mono_cmp) {
    monos.insert(0);
}

Polynomial &Polynomial::operator+=(const Polynomial &rhs) noexcept {
    if (isZero()) {
        *this = rhs;
    } else if (rhs.isZero()) {
        return *this;
    } else {
        for (const Monomial &m : rhs.monos) {
            auto it = monos.find(m);
            if (it == monos.cend()) {
                monos.insert(m);
            } else {
                Monomial sum = *it + m;
                monos.erase(it);
                if (sum.getCoefficient() != 0) {
                    monos.insert(sum);
                }
            }
        }
    }

    return *this;
}

Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs) noexcept {
    Polynomial result = lhs;
    result += rhs;
    return result;
}

Polynomial::Polynomial(std::initializer_list<Monomial> initMonos)
        : monos(mono_cmp) {
    for (const Monomial &m : initMonos) {
        monos.insert(m);
    }
}

Polynomial &Polynomial::operator-=(const Polynomial &rhs) noexcept {
    Polynomial rhs_neg;
    for (const Monomial &m : rhs.monos) {
        Monomial m_neg = m;
        m_neg.negate();
        rhs_neg += {m_neg};
    }

    *this += rhs_neg;
    return *this;
}

Polynomial operator-(const Polynomial &lhs, const Polynomial &rhs) noexcept {
    Polynomial result = lhs;
    result += rhs;
    return result;
}

std::string Polynomial::show() const noexcept {
    std::string result;
    if (monos.size() == 1) {
        result += monos.begin()->show(false, true);
    } else {
        bool isFirst = true;
        for (const Monomial &m : monos) {
            result += m.show(!isFirst);
            isFirst = false;
        }
    }
    return result;
}

Polynomial &Polynomial::operator*=(const Polynomial &rhs) noexcept {
    *this = *this * rhs;
    return *this;
}

Polynomial operator*(const Polynomial &lhs, const Polynomial &rhs) noexcept {
    Polynomial result = {0};
    if (lhs.isZero() || rhs.isZero()) {
        return result;
    }
    for (const Monomial &m : lhs.monos) {
        for (const Monomial &n : rhs.monos) {
            result += {m * n};
        }
    }
    return result;
}

int64_t Polynomial::evaluate(int64_t var) const noexcept {
    int64_t result = 0;
    for (const Monomial &m : monos) {
        result += m.evaluate(var);
    }
    return result;
}

Polynomial &Polynomial::derivation(int64_t times) noexcept {
    Polynomial result;
    for (const Monomial &m : monos) {
        Monomial dm = m;
        dm.derivation(times);
        result += {dm};
    }
    *this = result;
    return *this;
}

}
}
}
