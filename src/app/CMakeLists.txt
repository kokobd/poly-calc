project(poly-calc-app)

add_executable(${PROJECT_NAME} src/Main.cpp)

target_link_libraries(${PROJECT_NAME}
        poly-calc-service)
