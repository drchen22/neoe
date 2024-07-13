file(GLOB_RECURSE TEST_FILES "*.cpp")
add_executable(tests ${TEST_FILES})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tests PRIVATE NeoeRuntime)