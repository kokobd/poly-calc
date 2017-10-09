#include <catch/catch.hpp>

#include <poly-calc/service/expression/SimpleEvaluator.h>
#include <poly-calc/service/Executor.h>
#include <memory>

TEST_CASE("SimpleEvaluator") {
    using Zelinf::PolyCalc::Service::Expression::SimpleEvaluator;
    using Zelinf::PolyCalc::Service::Evaluator;
    using Zelinf::PolyCalc::Service::Executor;

    std::shared_ptr<Evaluator> evaluator;
    {
        // I should have choose an interface-based design, which will
        // allow easier mocking. For now, I have to use the Executor class
        // here.
        Executor exec; // This executor won't actually get executed.
        evaluator = std::make_shared<SimpleEvaluator>(exec);
    }

    // Below, test sections should use the evaluator exclusively.

    SECTION("binary operators (normal)") {
        REQUIRE("x^2\n" == evaluator->evaluate("1+x^2-1"));
        REQUIRE("x^2-1\n" == evaluator->evaluate("(x+1) * (x - 1)"));
        REQUIRE("x^3-3x^2+3x-1\n" == evaluator->evaluate("(x-1) ^ 3"));
        REQUIRE("1\n" == evaluator->evaluate("(2*x - 1)^0"));
        REQUIRE("1\n" == evaluator->evaluate("(2*x - 1)^(x - x)"));
        REQUIRE("2x-1\n" == evaluator->evaluate("(2*x - 1)^(x'1 + x - x)"));
        REQUIRE("20x^3\n" == evaluator->evaluate("(x^5)'2"));
        REQUIRE_NOTHROW(evaluator->evaluate("x^x"));
        REQUIRE_NOTHROW(evaluator->evaluate("x^(0-1)"));
        REQUIRE_NOTHROW(evaluator->evaluate("x'x"));
        REQUIRE_NOTHROW(evaluator->evaluate("x'(0-1)"));
    }
}
