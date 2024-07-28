#pragma once

#include <GLFW/glfw3.h>
#include <vector>
#include <vulkan/vulkan.h>
#include <runtime/function/interface/rhi.h>
#include <vulkan/vulkan_core.h>

namespace neoe {

class VulkanRHI final: public RHI {
public:
    // initialize
    virtual void initialize(RHIInitInfo init_info) override final;
    virtual void prepareContext() override final;

    virtual ~VulkanRHI() override final;
public:
    GLFWwindow* window_ {nullptr};
    VkInstance instance_ { nullptr };
    VkSurfaceKHR surface_ { nullptr };

    // function pointers
    // PFN_vkCmdBeginDebugUtilsLabelEXT _vkCmdBeginDebugUtilsLabelEXT;
    // PFN_vkCmdEndDebugUtilsLabelEXT   _vkCmdEndDebugUtilsLabelEXT;
private:
    const std::vector<char const*> validation_layers_ { "VK_LAYER_KHRONOS_validation" };
    uint32_t vulkan_api_version_ { VK_API_VERSION_1_0 };


private:
    void createInstance();
    void initializeDebugMessenger();
    void createWindowSurface();
    void initializePhysicalDevice();
    void createLogicalDevice();
    // void createCommandPool() override;
    void createCommandBuffers();
    void createDescriptorPool();
    void createSyncPrimitives();
    void createAssetAllocator();
// private:
public:
    bool enable_validation_layers_ = { true };
    bool enable_debug_utils_label_ = { true };

    bool checkValidationLayerSupport();
    std::vector<const char*> getRequiredExtensions();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    VkDebugUtilsMessengerEXT m_debug_messenger = nullptr;
    VkResult                 createDebugUtilsMessengerEXT(VkInstance                                instance,
                                                                  const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                                                  const VkAllocationCallbacks*              pAllocator,
                                                                  VkDebugUtilsMessengerEXT*                 pDebugMessenger);

    void                     destroyDebugUtilsMessengerEXT(VkInstance                   instance,
                                                           VkDebugUtilsMessengerEXT     debugMessenger,
                                                           const VkAllocationCallbacks* pAllocator);
};





}
