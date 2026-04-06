cmake_minimum_required(VERSION 3.16)
project(yastk C)

add_library(yastk STATIC
    yastk.c
    _internal_yastk.c
)

target_include_directories(yastk
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(yastk PROPERTIES
    C_STANDARD 99
    POSITION_INDEPENDENT_CODE ON
)

option(YASTK_BUILD_TESTS "Build tests for yastk" ON)

if(YASTK_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
