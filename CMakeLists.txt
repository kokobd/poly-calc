cmake_minimum_required(VERSION 3.8)
project(poly-calc)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(libs/catch)
add_subdirectory(libs/fmt-4.0.0)

enable_testing()

add_subdirectory(src/service)
add_subdirectory(src/app)
