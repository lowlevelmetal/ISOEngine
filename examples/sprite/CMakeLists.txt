add_executable(sprite sprite.c)

target_link_libraries(sprite PRIVATE isoengine)

add_custom_command(TARGET sprite POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/examples/sprite/assets
            $<TARGET_FILE_DIR:sprite>/assets
)