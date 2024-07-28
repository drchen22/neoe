set(TARGET_NAME SandBox)

file(GLOB_RECURSE SANDBOX_HEADERS "*.h" "*.hpp")
file(GLOB_RECURSE SANDBOX_SOURCES "*.cpp" "*.cc")

add_executable(${TARGET_NAME} ${SANDBOX_HEADERS} ${SANDBOX_SOURCES})

target_link_libraries(${TARGET_NAME} PUBLIC NeoeRuntime)
target_link_libraries(${TARGET_NAME} PUBLIC NeoeEditor)
