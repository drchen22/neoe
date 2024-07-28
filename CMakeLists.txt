cmake_minimum_required(VERSION 3.20)

project(neoe VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Catch2 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
if(Vulkan_FOUND)
    message("-------> Find vulkan include success: ${Vulkan_INCLUDE_DIRS}")
    message("-------> Find vulkan lbrary success: ${Vulkan_LIBRARY}")
    include_directories(${Vulkan_INCLUDE_DIRS})
endif()


add_subdirectory(tests)
add_subdirectory(engine)
add_subdirectory(examples/SandBox)
