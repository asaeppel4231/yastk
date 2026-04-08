cmake_minimum_required(VERSION 3.16)
project(yastk C)

add_library(yastk STATIC
    yastk.c
    _internal_yastk.c
)

target_include_directories(yastk
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

# Optionally include helpers.h for debug support
set(H2OT3_HELPERS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../core/helpers")
if(EXISTS "${H2OT3_HELPERS_PATH}/helpers.h")
    target_include_directories(yastk
        PRIVATE ${H2OT3_HELPERS_PATH}
    )
    message(STATUS "yastk: Found helpers.h for debug support")
else()
    message(STATUS "yastk: helpers.h not found, debug support disabled")
endif()

set_target_properties(yastk PROPERTIES
    C_STANDARD 99
    POSITION_INDEPENDENT_CODE ON
)

option(YASTK_BUILD_TESTS "Build tests for yastk" OFF)

if(YASTK_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
