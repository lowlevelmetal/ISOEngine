enable_testing()

add_executable(test_engine test_engine.c)
add_executable(test_object test_object.c)

target_link_libraries(test_engine PRIVATE isoengine)
target_link_libraries(test_object PRIVATE isoengine)

add_test(NAME test_engine COMMAND test_engine)
add_test(NAME test_object COMMAND test_object)