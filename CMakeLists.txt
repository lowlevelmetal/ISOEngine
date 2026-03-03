cmake_minimum_required(VERSION 4.0)
project(ISOEngine VERSION 0.0.0 LANGUAGES C)

if(ENV{CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_compile_definitions(_DEBUG)
endif()

set(SDL_SHARED OFF CACHE BOOL "Disable Shared" FORCE)
set(SDL_STATIC ON CACHE BOOL "Enable Static" FORCE)
add_subdirectory(3rd/SDL)

add_library(isoengine STATIC
    src/engine.c
    src/window.c
    src/render.c
    src/object.c
    src/memory.c
    src/clock.c
)

target_include_directories(isoengine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(isoengine PRIVATE SDL3::SDL3)

set_property(TARGET isoengine PROPERTY CMAKE_C_STANDARD 23)
set_property(TARGET isoengine PROPERTY CMAKE_C_STANDARD_REQUIRED ON)

## Tests

add_subdirectory(tests)

## Examples

add_subdirectory(examples)