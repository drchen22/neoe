#pragma once

#include <memory>
#include <GLFW/glfw3.h>

namespace neoe {
    struct WindowCreateInfo
    {
        int         width {1280};
        int         height {720};
        const char* title {"NeoE"};
        bool        is_fullscreen {false};
    };

    class WindowSystem {
    public:
        WindowSystem &operator=(WindowSystem &&) = delete;  // 删除五个构造，保留默认构造

        ~WindowSystem();

        void initialize(WindowCreateInfo create_info);
        void poolEvents() const;
        bool shouldClose() const;
        void setTitle(const char* title);
        GLFWwindow* getWindow() const;

    private:
        GLFWwindow* window_ {nullptr};
        int height_ {0};
        int width_ {0};
    };
}
