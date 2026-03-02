cmake_minimum_required(VERSION 4.0)
project(ISOEngine VERSION 0.0.0 LANGUAGES C)

set(SDL_SHARED OFF CACHE BOOL "Disable Shared" FORCE)
set(SDL_STATIC ON CACHE BOOL "Enable Static" FORCE)
add_subdirectory(3rd/SDL)

add_library(isoengine STATIC
    src/engine.c
    src/window.c
    src/render.c
)

target_include_directories(isoengine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(isoengine PRIVATE SDL3::SDL3)

set_property(TARGET isoengine PROPERTY CMAKE_C_STANDARD 23)
set_property(TARGET isoengine PROPERTY CMAKE_C_STANDARD_REQUIRED ON)

## Tests

enable_testing()

add_executable(test_engine tests/test_engine.c)

target_link_libraries(test_engine PRIVATE isoengine)

add_test(NAME test_engine COMMAND test_engine)

## Examples

add_subdirectory(examples)