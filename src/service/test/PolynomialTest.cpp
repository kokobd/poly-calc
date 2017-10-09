#include <catch/catch.hpp>
#include <poly-calc/service/poly/Polynomial.h>

using namespace Zelinf::PolyCalc::Service::Poly;

namespace Catch {
template<>
struct StringMaker<Polynomial> {
    static std::string convert(Polynomial const &p) {
        return p.show();
    }
};
}

TEST_CASE("Polynomial") {
    SECTION("show") {
        Polynomial p;
        REQUIRE(("2x^3+x^2" == Polynomial{{1, 2},
                                          {2, 3}}.show()));
        REQUIRE("0" == Polynomial{{0}}.show());
        REQUIRE("-1" == Polynomial{{-1}}.show());
        REQUIRE("1" == Polynomial({1}).show());
        REQUIRE("x^2-x" == Polynomial({{1,  2},
                                       {-1, 1}}).show());
        REQUIRE(("x^2" == Polynomial{{1, 2}}.show()));
        REQUIRE(("3" == Polynomial{{3}}.show()));
        p = {{2,  2},
             {-3, 1}};
        REQUIRE("2x^2-3x" == p.show());
    }

    SECTION("operator+") {
        Polynomial p1{0};
        Polynomial p2{{2, 3},
                      {3, 1}};
        REQUIRE(p2 == p1 + p2);
        Polynomial p3{{-1, 3},
                      {4,  2}};
        REQUIRE(Polynomial({{1, 3},
                            {4, 2},
                            {3, 1}}) == p2 + p3);
    }

    SECTION("operator-") {
        REQUIRE(Polynomial({{0}}) == Polynomial({{1, 1}}) - Polynomial({{1, 1}}));
        REQUIRE(Polynomial({{2, 1}}) == Polynomial({{1, 1}}) - Polynomial({{-1, 1}}));
    }

    SECTION("operator*") {
        REQUIRE(Polynomial({0}) == Polynomial({0}) * Polynomial({{2, 3},
                                                                 {1, 2}}));
        Polynomial p1 = {{1, 1},
                         {1}};
        Polynomial p2 = {{1, 1},
                         {-1}};
        Polynomial product = p1 * p2;
        REQUIRE(Polynomial({{1,  2},
                            {-1, 0}}) == product);
    }

    SECTION("derivation") {
        Polynomial p1 = {{1,  3},
                         {-2, 5}};
        REQUIRE(Polynomial({{3,   2},
                            {-10, 4}}) == p1.derivation(1));
        REQUIRE(Polynomial({0}) == p1.derivation(6));
    }

    SECTION("evaluate") {
        Polynomial p1 = {{1,  3},
                         {-2, 5}};
        REQUIRE(-459 == p1.evaluate(3));
        REQUIRE(0 == p1.evaluate(0));
        REQUIRE(-1 == p1.evaluate(1));
        REQUIRE(1 == p1.evaluate(-1));
    }

    SECTION("power") {
        Polynomial p1 = {{1, 1},
                         {-1}};
        REQUIRE(Polynomial({{1,  3},
                            {-3, 2},
                            {3,  1},
                            {-1}}) == p1.power(3));
        REQUIRE(Polynomial({{1}}) == p1.power(0));
        REQUIRE_THROWS_AS(p1.power(-1), std::invalid_argument);
    }
}