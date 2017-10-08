project(poly-calc-app)

add_executable(${PROJECT_NAME}
        src/Main.cpp
        src/Executor.h
        src/Executor.cpp
        src/Evaluator.h
        src/Command.h
        src/Command.cpp

        src/commands/Quit.h
        src/commands/Quit.cpp
        src/commands/Help.h
        src/commands/Help.cpp
        src/commands/Show.h
        src/commands/Show.cpp

        src/expression/ParseError.h
        src/expression/SimpleEvaluator.h
        src/expression/SimpleEvaluator.cpp
        src/expression/operators/BiOperator.h
        src/expression/operators/BiOperator.cpp
        src/expression/operators/Plus.h
        src/expression/operators/Plus.cpp
        src/expression/operators/Minus.h
        src/expression/operators/Minus.cpp
        src/expression/operators/Multiply.h
        src/expression/operators/Multiply.cpp
        src/expression/operators/Derivation.h
        src/expression/operators/Derivation.cpp
        )

target_link_libraries(${PROJECT_NAME}
        poly-calc-service
        fmt
        variant)
