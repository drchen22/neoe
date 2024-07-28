#include "runtime/function/interface/vulkan/vulkan_common.h"
#include "runtime/function/interface/vulkan/vulkan_rhi.h"
#include "runtime/function/render/window_system.h"
#include <iostream>
#include <memory>
#include <runtime/core/log/log_system.hpp>
#include <vulkan/vulkan_core.h>

int main() {
    std::cout << "Hello NeoE!" << std::endl;

    neoe::LogSystem::Init();

    std::shared_ptr<neoe::WindowSystem> window = std::make_unique<neoe::WindowSystem>();
    window->initialize({1280, 720, "NeoE", false});

    auto rhi = std::make_unique<neoe::VulkanRHI>();
    rhi->initialize({window});


    while (!window->shouldClose()) {
        window->poolEvents();
    }
    return 0;
}
