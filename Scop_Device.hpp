#pragma once
// Enable beta extensions (needed for VK_KHR_portability_subset)
#define VK_ENABLE_BETA_EXTENSIONS

// added because of error
#ifndef VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME
#define VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"
#endif

#include "Scop_Window.hpp"

// std-lib headers
#include <string>
#include <vector>
#include <vulkan/vulkan.h>

namespace scop {
struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

struct QueueFamilyIndices {
    uint32_t graphicsFamily;
    uint32_t presentFamily;
    bool graphicsFamilyHasValue = false;
    bool presentFamilyHasValue = false;
    bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue; }
};

class Scop_Device {
public:
#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

    explicit Scop_Device(Scop_Window &window);

    ~Scop_Device();

    // non-copyable / non-movable
    Scop_Device(const Scop_Device &) = delete;

    Scop_Device &operator=(const Scop_Device &) = delete;

    Scop_Device(Scop_Device &&) = delete;

    Scop_Device &operator=(Scop_Device &&) = delete;

    /* simple getters */
    VkDevice device() { return device_; }
    VkSurfaceKHR surface() { return surface_; }
    VkQueue graphicsQueue() { return graphicsQueue_; }
    VkQueue presentQueue() { return presentQueue_; }
    VkCommandPool getCommandPool() { return commandPool; }
    VkPhysicalDeviceProperties properties;

    SwapChainSupportDetails getSwapChainSupport() { return querySwapChainSupport(physicalDevice); }

    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    QueueFamilyIndices findPhysicalQueueFamilies() { return findQueueFamilies(physicalDevice); }

    VkFormat findSupportedFormat(
        const std::vector<VkFormat> &candidates,
        VkImageTiling tiling,
        VkFormatFeatureFlags features
    );

    /* buffer helpers */
    void createBuffer(
        VkDeviceSize size,
        VkBufferUsageFlags usage,
        VkMemoryPropertyFlags properties,
        VkBuffer &buffer,
        VkDeviceMemory &bufferMemory
    );

    VkCommandBuffer beginSingleTimeCommands();

    void endSingleTimeCommands(VkCommandBuffer commandBuffer);

    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    void copyBufferToImage(
        VkBuffer buffer,
        VkImage image,
        uint32_t width,
        uint32_t height,
        uint32_t layerCount
    );

    void createImageWithInfo(
        const VkImageCreateInfo &imageInfo,
        VkMemoryPropertyFlags properties,
        VkImage &image,
        VkDeviceMemory &imageMemory
    );

private:
    /* creation steps */
    void createInstance();

    void setupDebugMessenger();

    void createSurface();

    void pickPhysicalDevice();

    void createLogicalDevice();

    void createCommandPool();

    /* helpers */
    bool isDeviceSuitable(VkPhysicalDevice device);

    std::vector<const char *> getRequiredExtensions();

    bool checkValidationLayerSupport();

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

    void hasGflwRequiredInstanceExtensions();

    bool checkDeviceExtensionSupport(VkPhysicalDevice device);

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    Scop_Window &window;
    VkCommandPool commandPool;

    VkDevice device_;
    VkSurfaceKHR surface_;
    VkQueue graphicsQueue_;
    VkQueue presentQueue_;

    const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};

#ifdef __APPLE__
    const std::vector<const char *> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
        VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME // required by MoltenVK
    };
#else
    const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
#endif
};
} // namespace scop
