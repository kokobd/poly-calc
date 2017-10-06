project(poly-calc-service)

set(LIBNAME ${PROJECT_NAME})

add_library(${LIBNAME}
        include/poly-calc/service/Polynomial.h
        include/poly-calc/service/Monomial.h
        src/Polynomial.cpp
        src/Monomial.cpp
        )

target_include_directories(${LIBNAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(${LIBNAME}
        fmt)

set(TEST_NAME ${LIBNAME}-test)
add_executable(${TEST_NAME}
        test/TestMain.cpp
        test/MonomialTest.cpp
        test/PolynomialTest.cpp)
target_link_libraries(${TEST_NAME}
        catch
        ${LIBNAME})
add_test(${TEST_NAME} ${TEST_NAME})
