project(variant)

add_library(variant INTERFACE)

target_include_directories(variant INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/>)
