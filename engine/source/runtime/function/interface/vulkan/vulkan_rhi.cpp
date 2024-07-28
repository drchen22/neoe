#define GLFW_INCLUDE_VULKAN

#include "runtime/core/log/log_system.hpp"
#include "runtime/function/render/window_system.h"
#include <GLFW/glfw3.h>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <runtime/function/interface/vulkan/vulkan_rhi.h>
#include <vulkan/vulkan_core.h>

namespace neoe {

    VulkanRHI::~VulkanRHI() {
        vkDestroySurfaceKHR(instance_, surface_, nullptr);
        vkDestroyInstance(instance_, nullptr);
    }

void VulkanRHI::initialize(RHIInitInfo init_info) {
    window_ = init_info.window->getWindow();
    createInstance();

    createWindowSurface();
}

void VulkanRHI::prepareContext() {

}

// debug callback
static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT,
                                                    VkDebugUtilsMessageTypeFlagsEXT,
                                                    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                    void*)
{
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}

void VulkanRHI::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
{
    createInfo       = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity =
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType =
        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
}

void VulkanRHI::createInstance() {
    // check validation layer support in debug mode
    if (enable_validation_layers_ && !checkValidationLayerSupport()) {
        LOG_E("validation layer not supported");
    }

    vulkan_api_version_ = VK_API_VERSION_1_0;

    // app information
    VkApplicationInfo app_info {};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "NeoE";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "NeoE";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = vulkan_api_version_;

    // create instance
    VkInstanceCreateInfo instance_create_info {};
    instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance_create_info.pApplicationInfo = &app_info;

    auto extensions = getRequiredExtensions();
    instance_create_info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    instance_create_info.ppEnabledExtensionNames = extensions.data();

    // create debug utils messenger
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo {};
    if (enable_debug_utils_label_) {
        instance_create_info.enabledLayerCount = static_cast<uint32_t>(validation_layers_.size());
        instance_create_info.ppEnabledLayerNames = validation_layers_.data();

        populateDebugMessengerCreateInfo(debugCreateInfo);
        instance_create_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    } else {
        instance_create_info.enabledLayerCount = 0;
        instance_create_info.pNext = nullptr;
    }

    // create instance
    if (vkCreateInstance(&instance_create_info, nullptr, &instance_) != VK_SUCCESS) {
        LOG_E("failed to create instance");
    }
    LOG_T("instance created");
}


void VulkanRHI::createWindowSurface() {
    if (glfwCreateWindowSurface(instance_, window_, nullptr, &surface_) != VK_SUCCESS) {
        LOG_E("glfwCreateWindowSurface failed");
    }
    LOG_T("GLFW window surface created");
}

bool VulkanRHI::checkValidationLayerSupport() {
    uint32_t layerCount = 0;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for(auto& layer : availableLayers){
        LOG_T("supported layerName: {0}", layer.layerName);
    }

    for (const char* layerName : validation_layers_)
    {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers)
        {
            if (strcmp(layerName, layerProperties.layerName) == 0)
            {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
        {
            return false;
        }
    }
    return true;
}

std::vector<const char*> VulkanRHI::getRequiredExtensions()
{
    uint32_t     glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (enable_validation_layers_ || enable_debug_utils_label_)
    {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    for (auto& extension : extensions) {
        LOG_T("supported extension: {0}", extension);
    }

    return extensions;
}

// void VulkanRHI::initializeDebugMessenger()
// {
//     if (enable_validation_layers_)
//     {
//         VkDebugUtilsMessengerCreateInfoEXT createInfo;
//         populateDebugMessengerCreateInfo(createInfo);
//         if (VK_SUCCESS != createDebugUtilsMessengerEXT(instance_, &createInfo, nullptr, &m_debug_messenger))
//         {
//             LOG_E("failed to set up debug messenger!");
//         }
//     }

//     if (enable_debug_utils_label_)
//     {
//         _vkCmdBeginDebugUtilsLabelEXT =
//             (PFN_vkCmdBeginDebugUtilsLabelEXT)vkGetInstanceProcAddr(instance_, "vkCmdBeginDebugUtilsLabelEXT");
//         _vkCmdEndDebugUtilsLabelEXT =
//             (PFN_vkCmdEndDebugUtilsLabelEXT)vkGetInstanceProcAddr(instance_, "vkCmdEndDebugUtilsLabelEXT");
//     }
// }

// VkResult VulkanRHI::createDebugUtilsMessengerEXT(VkInstance                                instance,
//                                                      const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
//                                                      const VkAllocationCallbacks*              pAllocator,
//                                                      VkDebugUtilsMessengerEXT*                 pDebugMessenger)
//     {
//         auto func =
//             (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
//         if (func != nullptr)
//         {
//             return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
//         }
//         else
//         {
//             return VK_ERROR_EXTENSION_NOT_PRESENT;
//         }
//     }

//     void VulkanRHI::destroyDebugUtilsMessengerEXT(VkInstance                   instance,
//                                                   VkDebugUtilsMessengerEXT     debugMessenger,
//                                                   const VkAllocationCallbacks* pAllocator)
//     {
//         auto func =
//             (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
//         if (func != nullptr)
//         {
//             func(instance, debugMessenger, pAllocator);
//         }
//     }
}
