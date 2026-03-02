cmake_minimum_required(VERSION 4.0)
project(isoengine_window)

add_executable(isoengine_window window.c)

target_link_libraries(isoengine_window PRIVATE isoengine)