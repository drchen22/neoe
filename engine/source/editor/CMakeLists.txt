set(TARGET_NAME NeoeEditor)

# ---- Add source files ----
file(GLOB_RECURSE EDITOR_HEADERS "*.h" "*.hpp")
file(GLOB_RECURSE EDITOR_SOURCES "*.cpp" "*.cc")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

# ---- Add library ----
add_library(${TARGET_NAME} ${EDITOR_HEADERS} ${EDITOR_SOURCES})

set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 20)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Engine")

# ---- Link dependencies ----

target_link_libraries(${TARGET_NAME} PUBLIC spdlog::spdlog)

# ---- include directories ----
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/engine/source)
