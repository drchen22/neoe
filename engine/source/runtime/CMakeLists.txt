
set(TARGET_NAME NeoeRuntime)

# ---- Add source files ----
file(GLOB_RECURSE HEADER_FILES "*.h" "*.hpp")
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

# ---- Add library ----
add_library(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})

set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 20)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Engine")

# ---- Link dependencies ----



# ---- include directories ----
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/engine/source)