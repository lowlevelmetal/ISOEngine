cmake_minimum_required(VERSION 4.0)
project(ISOEngine VERSION 0.0.0 LANGUAGES C)

add_library(isoengine STATIC
    src/engine.c
)

target_include_directories(isoengine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(isoengine PUBLIC c_std_23)

## Tests

enable_testing()

add_executable(test_engine tests/test_engine.c)

target_link_libraries(test_engine PRIVATE isoengine)

add_test(NAME test_engine COMMAND test_engine)