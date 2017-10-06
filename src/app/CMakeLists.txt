project(poly-calc-app)

add_executable(${PROJECT_NAME}
        src/Main.cpp
        src/Executor.h
        src/Executor.cpp
        src/Evaluator.h
        src/Command.h

        src/commands/Quit.h
        src/commands/Quit.cpp)

target_link_libraries(${PROJECT_NAME}
        poly-calc-service
        fmt)
