project(poly-calc-service)

set(LIBNAME ${PROJECT_NAME})

add_library(${LIBNAME}
        include/poly-calc/service/poly/Polynomial.h
        include/poly-calc/service/poly/Monomial.h
        include/poly-calc/service/Command.h
        include/poly-calc/service/Executor.h
        include/poly-calc/service/Evaluator.h
        include/poly-calc/service/commands/Help.h
        include/poly-calc/service/commands/Show.h
        include/poly-calc/service/commands/Quit.h
        include/poly-calc/service/commands/Equals.h
        include/poly-calc/service/expression/BiOperator.h
        include/poly-calc/service/expression/ParseError.h
        include/poly-calc/service/expression/SimpleEvaluator.h
        include/poly-calc/service/expression/operators/Derivation.h
        include/poly-calc/service/expression/operators/Minus.h
        include/poly-calc/service/expression/operators/Multiply.h
        include/poly-calc/service/expression/operators/Plus.h
        include/poly-calc/service/expression/operators/Power.h

        src/poly/Polynomial.cpp
        src/poly/Monomial.cpp
        src/Command.cpp
        src/Executor.cpp
        src/commands/Help.cpp
        src/commands/Quit.cpp
        src/commands/Show.cpp
        src/commands/Equals.cpp
        src/expression/SimpleEvaluator.cpp
        src/expression/operators/BiOperator.cpp
        src/expression/operators/Derivation.cpp
        src/expression/operators/Minus.cpp
        src/expression/operators/Multiply.cpp
        src/expression/operators/Plus.cpp
        src/expression/operators/Power.cpp
        )

target_include_directories(${LIBNAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(${LIBNAME}
        fmt
        variant)

set(TEST_NAME ${LIBNAME}-test)
add_executable(${TEST_NAME}
        test/TestMain.cpp
        test/MonomialTest.cpp
        test/PolynomialTest.cpp
        test/SimpleEvaluatorTest.cpp
        )
target_link_libraries(${TEST_NAME}
        catch
        ${LIBNAME})
add_test(${TEST_NAME} ${TEST_NAME})
