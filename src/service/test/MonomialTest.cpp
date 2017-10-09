#include <catch/catch.hpp>
#include <poly-calc/service/poly/Monomial.h>

using namespace Zelinf::PolyCalc::Service::Poly;

namespace Catch {
template<>
struct StringMaker<Monomial> {
    static std::string convert(Monomial const &m) {
        return m.show(false, true);
    }
};
}

TEST_CASE("Monomial") {
    SECTION("Construction") {
        REQUIRE_THROWS_AS(Monomial(3, -1), std::invalid_argument);
        REQUIRE_NOTHROW(Monomial(3, 1));
    }

    SECTION("Evaluation") {
        Monomial defaultMono;
        REQUIRE(defaultMono.isConstant());
        REQUIRE(0 == defaultMono.evaluate(5));

        REQUIRE(Monomial(0, 4).isConstant());
        REQUIRE(0 == Monomial(0, 4).evaluate(3));
        REQUIRE(48 == Monomial(3, 4).evaluate(2));
    }

    SECTION("operator*=") {
        Monomial m1 = {3, 4};
        m1 *= Monomial(2, 3);
        REQUIRE(Monomial(6, 7) == m1);
        REQUIRE(Monomial(0) == m1 * Monomial(0, 4));
    }

    SECTION("show") {
        REQUIRE("0" == Monomial(0).show(false, true));
        REQUIRE("" == Monomial(0).show(false));
        REQUIRE("1" == Monomial(1).show(false));
        REQUIRE("+4" == Monomial(4).show(true));
        REQUIRE("2x^3" == Monomial(2, 3).show(false));
        REQUIRE("+2x^3" == Monomial(2, 3).show(true));
        REQUIRE("-2x^3" == Monomial(-2, 3).show(false));
    }

    SECTION("operator+=") {
        REQUIRE(Monomial(4, 3) == Monomial(1, 3) + Monomial(3, 3));
        REQUIRE(Monomial(4, 3) == Monomial(4, 3) + Monomial(0));

        REQUIRE_THROWS_AS(Monomial(2, 3) + Monomial(1, 4), std::invalid_argument);
    }

    SECTION("derivation") {
        REQUIRE(Monomial(12, 2) == Monomial(4, 3).derivation(1));
        REQUIRE(Monomial(24, 1) == Monomial(4, 3).derivation(2));
        REQUIRE(Monomial(0) == Monomial(3, 5).derivation(6));
    }
}
