#include "runtime/core/log/log_system.hpp"
#include <GLFW/glfw3.h>
#include <memory>
#include <runtime/function/render/window_system.h>
#include <unistd.h>

namespace neoe {
    WindowSystem::~WindowSystem()
    {
        glfwDestroyWindow(window_);
        glfwTerminate();
    }

    void WindowSystem::initialize(WindowCreateInfo create_info) {
        if(!glfwInit()) {
            LOG_F("Failed to initialize GLFW");
            return;
        }
        height_ = create_info.height;
        width_ = create_info.width;

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        window_ = glfwCreateWindow(create_info.width, create_info.height, create_info.title, nullptr, nullptr);
        if (!window_) {
            LOG_F("Failed to create window");
            glfwTerminate();
            return;
        }

        // GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        // if (create_info.is_fullscreen) {
        //     int xPos, yPos, workWidth, workHeight;
        //     glfwGetMonitorWorkarea(monitor, &xPos, &yPos, &workWidth, &workHeight);
        //     glfwSetWindowPos(window_, workWidth / 2 , workHeight / 2);
        // }

        glfwShowWindow(window_);
    }

    bool WindowSystem::shouldClose() const {
        return glfwWindowShouldClose(window_);
    }

    void WindowSystem::poolEvents() const {
        glfwPollEvents();
    }

    GLFWwindow* WindowSystem::getWindow() const {
        return window_;
    }
}
