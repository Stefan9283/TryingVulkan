#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <optional>
#include <set>
#include <string>


#include <array>
#include <bitset>

#include "glm.hpp"
// to be used for shader compilation at runtime
//#include "glslang/SPIRV/GlslangToSpv.h"
//#include "glslang/Public/ShaderLang.h"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;
const int MAX_FRAMES_IN_FLIGHT = 2;


#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

#ifdef _WIN32

#define ASSERT(x) if (!(x)) __debugbreak();

#define checkcall(x)\
    VkResult r = x;\
    ASSERT(utils::CheckError(r, #x, __FILE__, __LINE__))
#else

#define checkcall(x)\
        x;

#endif

namespace utils
{
    template <class T>
    std::vector<T> getData(VkResult(*f)(uint32_t*, T*))
    {
        uint32_t count = 0;

        if (f(&count, NULL) != VK_SUCCESS)
            throw std::runtime_error("Could't get entities count\n");

        std::vector<T> data(count);

        if (f(&count, data.data()) != VK_SUCCESS)
            throw std::runtime_error("Could't get data\n");

        return data;
    }

    template <class T, class S>
    std::vector<T> getData(S param, VkResult(*f)(S, uint32_t*, T*))
    {
        uint32_t count = 0;

        if (f(param, &count, NULL) != VK_SUCCESS)
            throw std::runtime_error("Could't get entities count\n");

        std::vector<T> data(count);

        if (f(param, &count, data.data()) != VK_SUCCESS)
            throw std::runtime_error("Could't get data\n");

        return data;
    }

    template <class T, class S>
    std::vector<T> getData(S param, void (*f)(S, uint32_t*, T*))
    {
        uint32_t count = 0;
        f(param, &count, NULL);
        std::vector<T> data(count);

        f(param, &count, data.data());

        return data;
    }

    template <class T, class S>
    std::vector<T> getData(S param, VkResult(*f)(S, const char*, uint32_t*, T*))
    {
        uint32_t count = 0;

        if (f(param, NULL, &count, NULL) != VK_SUCCESS)
            throw std::runtime_error("Could't get entities count\n");

        std::vector<T> data(count);

        if (f(param, NULL, &count, data.data()) != VK_SUCCESS)
            throw std::runtime_error("Could't get data\n");

        return data;
    }

    template <class T, class S, class U>
    std::vector<T> getData(S param1, U param2, VkResult(*f)(S, U, uint32_t*, T*))
    {
        uint32_t count = 0;

        if (f(param1, param2, &count, NULL) != VK_SUCCESS)
            throw std::runtime_error("Could't get entities count\n");

        std::vector<T> data(count);

        if (f(param1, param2, &count, data.data()) != VK_SUCCESS)
            throw std::runtime_error("Could't get data\n");

        return data;
    }




    int getErrors(VkResult r)
    {
        switch (r)
        {
            case 1:
                std::cout << "VK_NOT_READY\n";
            case 2:
                std::cout << " VK_TIMEOUT " << "\n";
                break;
            case 3:
                std::cout << " VK_EVENT_SET " << "\n";
                break;
            case 4:
                std::cout << " VK_EVENT_RESET " << "\n";
                break;
            case 5:
                std::cout << " VK_INCOMPLETE " << "\n";
                break;
            case -1:
                std::cout << " VK_ERROR_OUT_OF_HOST_MEMORY " << "\n";
                break;
            case -2:
                std::cout << " VK_ERROR_OUT_OF_DEVICE_MEMORY " << "\n";
                break;
            case -3:
                std::cout << " VK_ERROR_INITIALIZATION_FAILED " << "\n";
                break;
            case -4:
                std::cout << " VK_ERROR_DEVICE_LOST " << "\n";
                break;
            case -5:
                std::cout << " VK_ERROR_MEMORY_MAP_FAILED " << "\n";
                break;
            case -6:
                std::cout << " VK_ERROR_LAYER_NOT_PRESENT " << "\n";
                break;
            case -7:
                std::cout << " VK_ERROR_EXTENSION_NOT_PRESENT " << "\n";
                break;
            case -8:
                std::cout << " VK_ERROR_FEATURE_NOT_PRESENT " << "\n";
                break;
            case -9:
                std::cout << " VK_ERROR_INCOMPATIBLE_DRIVER " << "\n";
                break;
            case -10:
                std::cout << " VK_ERROR_TOO_MANY_OBJECTS " << "\n";
                break;
            case -11:
                std::cout << " VK_ERROR_FORMAT_NOT_SUPPORTED " << "\n";
                break;
            case -12:
                std::cout << " VK_ERROR_FRAGMENTED_POOL " << "\n";
                break;
            case -13:
                std::cout << " VK_ERROR_UNKNOWN " << "\n";
                break;
            case -1000069000:
                std::cout << " VK_ERROR_OUT_OF_POOL_MEMORY " << "\n";
                break;
            case -1000072003:
                std::cout << " VK_ERROR_INVALID_EXTERNAL_HANDLE " << "\n";
                break;
            case -1000161000:
                std::cout << " VK_ERROR_FRAGMENTATION " << "\n";
                break;
            case -1000257000:
                std::cout << " VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS " << "\n";
                break;
            case -1000000000:
                std::cout << " VK_ERROR_SURFACE_LOST_KHR " << "\n";
                break;
            case -1000000001:
                std::cout << " VK_ERROR_NATIVE_WINDOW_IN_USE_KHR " << "\n";
                break;
            case 1000001003:
                std::cout << " VK_SUBOPTIMAL_KHR " << "\n";
                break;
            case -1000001004:
                std::cout << " VK_ERROR_OUT_OF_DATE_KHR " << "\n";
                break;
            case -1000003001:
                std::cout << " VK_ERROR_INCOMPATIBLE_DISPLAY_KHR " << "\n";
                break;
            case -1000011001:
                std::cout << " VK_ERROR_VALIDATION_FAILED_EXT " << "\n";
                break;
            case -1000012000:
                std::cout << " VK_ERROR_INVALID_SHADER_NV " << "\n";
                break;
            case -1000150000:
                std::cout << " VK_ERROR_INCOMPATIBLE_VERSION_KHR " << "\n";
                break;
            case -1000158000:
                std::cout << " VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT " << "\n";
                break;
            case -1000174001:
                std::cout << " VK_ERROR_NOT_PERMITTED_EXT " << "\n";
                break;
            case -1000255000:
                std::cout << " VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT " << "\n";
                break;
            case 1000268000:
                std::cout << " VK_THREAD_IDLE_KHR " << "\n";
                break;
            case 1000268001:
                std::cout << " VK_THREAD_DONE_KHR " << "\n";
                break;
            case 1000268002:
                std::cout << " VK_OPERATION_DEFERRED_KHR " << "\n";
                break;
            case 1000268003:
                std::cout << " VK_OPERATION_NOT_DEFERRED_KHR " << "\n";
                break;
            case 1000297000:
                std::cout << " VK_PIPELINE_COMPILE_REQUIRED_EXT " << "\n";
                break;

        }
        return  r;
    }

    bool CheckError(VkResult code, const char* function, const char* file, int line)
    {
        return (getErrors(code) == 0);
    }

}
namespace wrappers
{
    std::vector<VkLayerProperties> getLayers()
    {
        std::vector<VkLayerProperties> layers = utils::getData(vkEnumerateInstanceLayerProperties);
        return layers;
    }



    namespace swapchain
    {
        std::vector<VkSurfaceFormatKHR> getSurfaceFormats(VkPhysicalDevice device, VkSurfaceKHR surface)
        {
            std::vector<VkSurfaceFormatKHR> formats = utils::getData(device, surface, vkGetPhysicalDeviceSurfaceFormatsKHR);
            return formats;
        }

        std::vector<VkPresentModeKHR> getPresentModes(VkPhysicalDevice device, VkSurfaceKHR surface)
        {
            std::vector<VkPresentModeKHR> formats = utils::getData(device, surface, vkGetPhysicalDeviceSurfacePresentModesKHR);
            return formats;
        }
        VkSurfaceCapabilitiesKHR getSurfaceCapabilities(VkPhysicalDevice device, VkSurfaceKHR surface)
        {
            VkSurfaceCapabilitiesKHR surfCapabilities;
            vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &surfCapabilities);
            return surfCapabilities;
        }
        std::vector<VkImage> getSwapChainImages(VkDevice device, VkSwapchainKHR swapchain)
        {
            std::vector<VkImage> images = utils::getData(device, swapchain, vkGetSwapchainImagesKHR);
            return images;
        }


    }
    namespace queuefamilies
    {
        std::vector<VkQueueFamilyProperties> getQueueFamilyProperties(VkPhysicalDevice device)
        {
            std::vector<VkQueueFamilyProperties> Properties = utils::getData(device, vkGetPhysicalDeviceQueueFamilyProperties);
            return Properties;
        }
    };
    namespace gpu
    {

        std::vector<VkPhysicalDevice> getGPUS(VkInstance instance)
        {
            std::vector<VkPhysicalDevice> gpus = utils::getData(instance, vkEnumeratePhysicalDevices);
            return gpus;
        }

        std::vector<VkExtensionProperties> getExtensions(VkPhysicalDevice device)
        {
            std::vector<VkExtensionProperties> ext = utils::getData(device, vkEnumerateDeviceExtensionProperties);
            return ext;
        }


        void ListExtensions(VkPhysicalDevice device)
        {
            VkPhysicalDeviceProperties properties;
            vkGetPhysicalDeviceProperties(device, &properties);
            std::cout << "\t" << properties.deviceName << "\n";


            std::vector<VkExtensionProperties> extensions = wrappers::gpu::getExtensions(device);


            std::cout << "\tSupported extensions:\n";
            for (auto extension : extensions)
            {
                std::cout << "\t\t" << extension.extensionName << "\n";
            }
        }

        int rateGPU(VkPhysicalDevice device)
        {
            int score = 0;

            VkPhysicalDeviceProperties Properties;
            vkGetPhysicalDeviceProperties(device, &Properties);

            if (Properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
                score += 1000;
            }
            score += Properties.limits.maxImageDimension2D;

            return score;
        }

        bool compareRatedGPUs(std::pair<VkPhysicalDevice, int> GPUa, std::pair<VkPhysicalDevice, int>GPUb)
        {
            return GPUa.second > GPUb.second;
        }


        bool checkGPUExtensionsSupport(VkPhysicalDevice device, std::vector<const char*> required_ext)
        {
            VkPhysicalDeviceProperties properties;
            vkGetPhysicalDeviceProperties(device, &properties);

            std::vector<VkExtensionProperties> extensions = wrappers::gpu::getExtensions(device);

            for (auto req : required_ext)
            {
                bool found = false;

                for (auto extension : extensions)
                {
                    if (!strcmp(extension.extensionName, req))
                    {
                        found = true;
                        break;
                    }
                    //std::cout << "\t\t" << extension.extensionName << "\n";
                }

                if (!found)
                    return false;//throw std::runtime_error("Extension is not supported\n");
            }

            return true;

        }


        bool isGPUSuitable(VkPhysicalDevice device, VkSurfaceKHR surface, std::vector<const char*> required_ext)
        {
            VkPhysicalDeviceFeatures features;
            VkPhysicalDeviceProperties properties;

            vkGetPhysicalDeviceProperties(device, &properties);
            vkGetPhysicalDeviceFeatures(device, &features);

            //ListExtensions(device);

            std::vector<VkSurfaceFormatKHR> formats = wrappers::swapchain::getSurfaceFormats(device, surface);
            std::vector<VkPresentModeKHR> presModes = wrappers::swapchain::getPresentModes(device, surface);

            bool ext_support = checkGPUExtensionsSupport(device, required_ext);

            return properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && features.geometryShader && ext_support && formats.size() && presModes.size();

        }

        VkPhysicalDevice SelectGPU(VkInstance instance, VkSurfaceKHR surface, std::vector<const char*> required_ext)
        {
            VkPhysicalDevice device = VK_NULL_HANDLE;

            std::vector<VkPhysicalDevice> gpus = wrappers::gpu::getGPUS(instance);

            std::vector < std::pair<VkPhysicalDevice, int>> ratedGPUs;
            for (auto gpu : gpus)
            {
                std::pair<VkPhysicalDevice, int> Pair;
                int score = rateGPU(gpu);
                Pair = std::make_pair(gpu, score);
                ratedGPUs.push_back(Pair);
            }

            std::sort(ratedGPUs.begin(), ratedGPUs.end(), compareRatedGPUs);

            for (auto pair : ratedGPUs)
            {
                VkPhysicalDeviceProperties Properties;
                vkGetPhysicalDeviceProperties(pair.first, &Properties);

                std::cout << Properties.deviceName << " score:" << pair.second << "\n";
                if (isGPUSuitable(pair.first, surface, required_ext))
                {
                    device = pair.first;
                    break;
                }
            }
            if (device == VK_NULL_HANDLE)
                throw std::runtime_error("No GPU was selected\n");

            return device;

        }

    }



}

class Extensions
{
public:

    std::vector<const char*> requiredExtensions = { VK_EXT_DEBUG_UTILS_EXTENSION_NAME };
    std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

    Extensions() {};
    ~Extensions() {};

    void getRequiredExtensions()
    {
        uint32_t count;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&count);

        for (uint32_t i = 0; i < count; i++)
        {
            requiredExtensions.push_back(glfwExtensions[i]);
        }
    }
};
class ValidationLayers
{
public:
    ValidationLayers() {};
    ~ValidationLayers() {};

    const std::vector<const char*> requiredValidationLayers = { "VK_LAYER_KHRONOS_validation" };
    bool checkSupport()
    {
        std::vector<VkLayerProperties> layers = wrappers::getLayers();

        for (auto required : requiredValidationLayers)
        {
            bool found = false;
            //std::cout << required << "\n";
            for (auto layer : layers)
            {
                std::cout << "\t" << layer.layerName << "\n";
                //std::cout << "\t" << layer.layerName << "\n";
                if (!strcmp(layer.layerName, required))
                {
                    found = true;
                    break;
                }

            }

            if (!found)
            {
                std::cout << required << "\n";
                throw std::runtime_error("Could't find required extension");
                return false;

            }
        }
        return true;

    }

};


static std::vector<char> readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}

struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        return attributeDescriptions;
    }
};


class VulkanProgram
{
public:
    Extensions Ext;
    ValidationLayers valLay;

    VkInstance instance;
    VkDevice device;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

    VkQueue presentationQueue = VK_NULL_HANDLE, graphicsQueue = VK_NULL_HANDLE;
    uint32_t presentationQueueIndex = -1, graphicsQueueIndex = -1;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;

    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    std::vector<VkImageView> swapChainImageViews;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;
    size_t currentFrame = 0;

    VkPipeline graphicsPipeline;


    std::vector<VkFramebuffer> swapChainFramebuffers;

    const std::vector<Vertex> vertices = {
    {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
    {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
    {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
    };

    void run()
    {

        initWindow();
        initVulkan();
        setupDebugMessenger();
        Loop();
        ClearUp();
    }

#pragma region DEBUG
    VkDebugUtilsMessengerEXT debugMessenger;


    /* Was is das ?????????*/
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"); // "__stdcall" ???
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        }
        else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"); // "__stdcall" ???
        if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
        }
    }
    /* Was is das ?????????*/

    void setupDebugMessenger() {
        if (!enableValidationLayers) return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo;
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                     VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                     VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = NULL;
        createInfo.flags = 0;


        checkcall(CreateDebugUtilsMessengerEXT(instance, &createInfo, NULL, &debugMessenger));

    }

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData) {

        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    }
#pragma endregion

private:
    GLFWwindow* window;
    void initWindow()
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;

    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;

#pragma region initVulkan

    void initVulkan()
    {
        std::cout << "Initializing the engine...\n";
        genInstance();
        genSurface();
        genDevice();
        genSwapChain();
        genImageViews();
        createRenderPass();
        createGraphicsPipelineLayout();
        createFramebuffers();
        createCommandPool();
        createCommandBuffers();
        createSyncObjects();

    }
    void createSyncObjects() {
        imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
        imagesInFlight.resize(swapChainImages.size(), VK_NULL_HANDLE);

        VkSemaphoreCreateInfo semaphoreInfo{};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfo{};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
                vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
                vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create synchronization objects for a frame!");
            }
        }
    }
    void createCommandBuffers() {
        commandBuffers.resize(swapChainFramebuffers.size());
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

        if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffers!");
        }
        for (size_t i = 0; i < commandBuffers.size(); i++) {
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            beginInfo.flags = 0; // Optional
            beginInfo.pInheritanceInfo = nullptr; // Optional

            if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
                throw std::runtime_error("failed to begin recording command buffer!");
            }

            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = renderPass;
            renderPassInfo.framebuffer = swapChainFramebuffers[i];
            renderPassInfo.renderArea.offset = { 0, 0 };
            renderPassInfo.renderArea.extent = swapChainExtent;

            VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
            renderPassInfo.clearValueCount = 1;
            renderPassInfo.pClearValues = &clearColor;

            vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

            vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

            vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

            vkCmdEndRenderPass(commandBuffers[i]);

            if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to record command buffer!");
            }
        }

    }
    void createCommandPool() {
        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = graphicsQueueIndex;
        poolInfo.flags = 0; // Optional

        if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create command pool!");
        }
    }
    void createFramebuffers() {
        swapChainFramebuffers.resize(swapChainImageViews.size());

        for (size_t i = 0; i < swapChainImageViews.size(); i++) {

            VkImageView attachments[] = {
                swapChainImageViews[i]
            };

            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = renderPass;
            framebufferInfo.attachmentCount = 1;
            framebufferInfo.pAttachments = attachments;
            framebufferInfo.width = swapChainExtent.width;
            framebufferInfo.height = swapChainExtent.height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create framebuffer!");
            }

        }
    }
    void createRenderPass() {
        VkAttachmentDescription colorAttachment{};
        colorAttachment.format = swapChainImageFormat;
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference colorAttachmentRef{};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;

        VkSubpassDependency dependency{};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        VkRenderPassCreateInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = 1;
        renderPassInfo.pAttachments = &colorAttachment;
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;
        renderPassInfo.dependencyCount = 1;
        renderPassInfo.pDependencies = &dependency;

        if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
            throw std::runtime_error("failed to create render pass!");
        }
    }
    VkShaderModule createShaderModule(const std::vector<char>& code)
    {
        VkShaderModuleCreateInfo create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        create_info.codeSize = code.size();
        create_info.pCode = reinterpret_cast<const uint32_t*>(code.data());
        VkShaderModule shaderModule;
        if (vkCreateShaderModule(device, &create_info, nullptr, &shaderModule) != VK_SUCCESS) {
            throw std::runtime_error("failed to create shader module!");
        }

        return shaderModule;

    }
    void createGraphicsPipelineLayout()
    {
        auto vertShaderCode = readFile("Dependencies/shaders/vert.spv");
        auto fragShaderCode = readFile("Dependencies/shaders/frag.spv");

        VkShaderModule vertShaderModule = createShaderModule(vertShaderCode);
        VkShaderModule fragShaderModule = createShaderModule(fragShaderCode);

        VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
        vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vertShaderStageInfo.module = vertShaderModule;
        vertShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
        fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fragShaderStageInfo.module = fragShaderModule;
        fragShaderStageInfo.pName = "main";


        VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

        /// /////////////////////////////

        auto bindingDescription = Vertex::getBindingDescription();
        auto attributeDescriptions = Vertex::getAttributeDescriptions();

        VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
        vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertexInputInfo.vertexBindingDescriptionCount = 1;
        vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
        vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
        vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

        VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
        inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        inputAssembly.primitiveRestartEnable = VK_FALSE;

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)swapChainExtent.width;
        viewport.height = (float)swapChainExtent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor{};
        scissor.offset = { 0, 0 };
        scissor.extent = swapChainExtent;

        VkPipelineViewportStateCreateInfo viewportState{};
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.pViewports = &viewport;
        viewportState.scissorCount = 1;
        viewportState.pScissors = &scissor;

        VkPipelineRasterizationStateCreateInfo rasterizer{};
        rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizer.depthClampEnable = VK_FALSE;

        rasterizer.rasterizerDiscardEnable = VK_FALSE;

        rasterizer.polygonMode = VK_POLYGON_MODE_FILL;

        rasterizer.lineWidth = 1.0f;

        rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
        rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;

        rasterizer.depthBiasEnable = VK_FALSE;
        rasterizer.depthBiasConstantFactor = 0.0f; // Optional
        rasterizer.depthBiasClamp = 0.0f; // Optional
        rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

        VkPipelineMultisampleStateCreateInfo multisampling{};
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.sampleShadingEnable = VK_FALSE;
        multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        multisampling.minSampleShading = 1.0f; // Optional
        multisampling.pSampleMask = nullptr; // Optional
        multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
        multisampling.alphaToOneEnable = VK_FALSE; // Optional

        VkPipelineColorBlendAttachmentState colorBlendAttachment{};
        colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

        /*
        colorBlendAttachment.blendEnable = VK_FALSE;
        colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
        colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
        colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
        colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
        colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
        colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional
        */

        // Alpha Blending
        colorBlendAttachment.blendEnable = VK_TRUE;
        colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
        colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

        VkPipelineColorBlendStateCreateInfo colorBlending{};
        colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorBlending.logicOpEnable = VK_FALSE;
        colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
        colorBlending.attachmentCount = 1;
        colorBlending.pAttachments = &colorBlendAttachment;
        colorBlending.blendConstants[0] = 0.0f; // Optional
        colorBlending.blendConstants[1] = 0.0f; // Optional
        colorBlending.blendConstants[2] = 0.0f; // Optional
        colorBlending.blendConstants[3] = 0.0f; // Optional

        VkDynamicState dynamicStates[] = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_LINE_WIDTH
        };

        VkPipelineDynamicStateCreateInfo dynamicState{};
        dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamicState.dynamicStateCount = 2;
        dynamicState.pDynamicStates = dynamicStates;

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0; // Optional
        pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
        pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
        pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

        if (vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout!");
        }
        //

        VkGraphicsPipelineCreateInfo pipelineInfo{};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.stageCount = 2;
        pipelineInfo.pStages = shaderStages;

        pipelineInfo.pVertexInputState = &vertexInputInfo;
        pipelineInfo.pInputAssemblyState = &inputAssembly;
        pipelineInfo.pViewportState = &viewportState;
        pipelineInfo.pRasterizationState = &rasterizer;
        pipelineInfo.pMultisampleState = &multisampling;
        pipelineInfo.pDepthStencilState = nullptr; // Optional
        pipelineInfo.pColorBlendState = &colorBlending;
        pipelineInfo.pDynamicState = nullptr; // Optional

        pipelineInfo.layout = pipelineLayout;

        pipelineInfo.renderPass = renderPass;
        pipelineInfo.subpass = 0;

        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
        pipelineInfo.basePipelineIndex = -1; // Optional

        if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
            throw std::runtime_error("failed to create graphics pipeline!");
        }


        vkDestroyShaderModule(device, fragShaderModule, nullptr);
        vkDestroyShaderModule(device, vertShaderModule, nullptr);

    }
    void genImageViews()
    {
        swapChainImageViews.resize(swapChainImages.size());


        for (auto i = 0; i < swapChainImages.size(); i++) {
            VkImageViewCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.image = swapChainImages[i];
            createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            createInfo.format = swapChainImageFormat;
            createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            createInfo.subresourceRange.baseMipLevel = 0;
            createInfo.subresourceRange.levelCount = 1;
            createInfo.subresourceRange.baseArrayLayer = 0;
            createInfo.subresourceRange.layerCount = 1;
            if (vkCreateImageView(device, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create image views!");
            }
        }


    }
    struct QueueFamilyIndices
    {
        int graphics = -1, presentation = -1;
        bool isComplete()
        {
            return (graphics != -1) && (presentation != -1);
        }
    };
    void genSurface() {
        if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }
    void genSwapChain()
    {
        std::cout << "Creating the swapchain...\n";

        std::vector<VkSurfaceFormatKHR> formats = wrappers::swapchain::getSurfaceFormats(physicalDevice, surface);
        std::vector<VkPresentModeKHR> presModes = wrappers::swapchain::getPresentModes(physicalDevice, surface);
        VkSurfaceCapabilitiesKHR capabilities = wrappers::swapchain::getSurfaceCapabilities(physicalDevice, surface);


        //for (auto form : formats)
        //    std::cout << form.format << "\n";
        //https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkFormat.html


        // choose a surface format
        VkSurfaceFormatKHR surfaceFormat;
        for (const auto& forms : formats) {
            if (forms.format == VK_FORMAT_B8G8R8A8_SRGB && forms.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                surfaceFormat = forms;
                break;
            }
        }

        // choose a presentation mode
        VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;
        for (const auto& pm : presModes) {
            if (pm == VK_PRESENT_MODE_MAILBOX_KHR) { // look for triple buffering
                presentMode = pm;
                break;
            }
        }




        // choose swap extent
        VkExtent2D actualExtent;

        if (capabilities.currentExtent.width != UINT32_MAX)
        {
            actualExtent = capabilities.currentExtent;
        }
        else
        {
            actualExtent = { WIDTH, HEIGHT };
            actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
            actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));
        }

        // create the swapchain

        uint32_t imageCount = capabilities.minImageCount;

        if (imageCount + 1 <= capabilities.maxImageCount && imageCount != 0) {
            imageCount++;
        }


        VkSwapchainCreateInfoKHR create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        create_info.surface = surface;
        create_info.minImageCount = imageCount;
        create_info.imageFormat = surfaceFormat.format;
        create_info.imageColorSpace - surfaceFormat.colorSpace;
        create_info.imageExtent = actualExtent;
        create_info.imageArrayLayers = 1;
        create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        uint32_t queueFamilyIndices[] = { graphicsQueueIndex, presentationQueueIndex };

        if (graphicsQueue != presentationQueue) {
            create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            create_info.queueFamilyIndexCount = 2;
            create_info.pQueueFamilyIndices = queueFamilyIndices;
        }
        else {
            create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            create_info.queueFamilyIndexCount = 0; // Optional
            create_info.pQueueFamilyIndices = nullptr; // Optional
        }

        create_info.preTransform = capabilities.currentTransform;
        create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        create_info.presentMode = presentMode;
        create_info.clipped = VK_TRUE;
        create_info.oldSwapchain = VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(device, &create_info, nullptr, &swapChain) != VK_SUCCESS) {
            throw std::runtime_error("failed to create swap chain!");
        }

        swapChainImages = wrappers::swapchain::getSwapChainImages(device, swapChain);

        swapChainImageFormat = surfaceFormat.format;
        swapChainExtent = actualExtent;
    }
    void genDevice()
    {
        physicalDevice = wrappers::gpu::SelectGPU(instance, surface, Ext.deviceExtensions);


        std::vector<VkQueueFamilyProperties> Qprop = wrappers::queuefamilies::getQueueFamilyProperties(physicalDevice);

        QueueFamilyIndices fam;

        bool found = false;
        for (unsigned int i = 0; i < Qprop.size(); i++) {
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);
            std::bitset<8> flags(Qprop[i].queueFlags);
            std::cout << flags << "\n";

            if (presentSupport)
            {
                fam.presentation = i;
            }


            if (Qprop[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {  // flags specified as bits
                //queue_info.queueFamilyIndex
                fam.graphics = i;
                found = true;
                break;
            }
        }

        if (!fam.isComplete())
            throw std::runtime_error("No QueueFamily was selected\n");

        std::set<uint32_t> uniqueQueueFamilies = { (uint32_t)fam.presentation, (uint32_t)fam.graphics };
        graphicsQueueIndex = fam.graphics;
        presentationQueueIndex = fam.presentation;

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

        float queue_priority = 1.0f;
        for (auto qFamily : uniqueQueueFamilies)
        {
            VkDeviceQueueCreateInfo queue_info = {};
            queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queue_info.pNext = NULL;
            queue_info.queueCount = 1;
            queue_info.pQueuePriorities = &queue_priority;
            queueCreateInfos.push_back(queue_info);
        }

        VkDeviceCreateInfo device_info = {};
        device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        device_info.pNext = NULL;
        device_info.queueCreateInfoCount = (uint32_t)(queueCreateInfos.size());
        device_info.pQueueCreateInfos = queueCreateInfos.data();
        device_info.enabledExtensionCount = (uint32_t)Ext.deviceExtensions.size();
        device_info.ppEnabledExtensionNames = Ext.deviceExtensions.data();
        device_info.enabledLayerCount = (uint32_t)valLay.requiredValidationLayers.size();
        device_info.ppEnabledLayerNames = valLay.requiredValidationLayers.data();
        device_info.pEnabledFeatures = NULL;

        if (vkCreateDevice(physicalDevice, &device_info, NULL, &device) != VK_SUCCESS)
            throw std::runtime_error("Could't create logical device!");

        vkGetDeviceQueue(device, fam.graphics, NULL, &graphicsQueue);
        vkGetDeviceQueue(device, fam.presentation, NULL, &presentationQueue);
    }
    void genInstance()
    {
        /* VULKAN_KEY_START */

        // initialize the VkApplicationInfo structure
        VkApplicationInfo app_info = {};
        app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pNext = NULL;
        app_info.pApplicationName = "cow.exe";
        app_info.applicationVersion = 0.000000069;
        app_info.pEngineName = "Umbra";
        app_info.engineVersion = 0.0000000420;
        app_info.apiVersion = VK_API_VERSION_1_0;

        // initialize the VkInstanceCreateInfo structure
        VkInstanceCreateInfo inst_info = {};
        inst_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        inst_info.pNext = NULL;
        inst_info.flags = 0;
        inst_info.pApplicationInfo = &app_info;
        Ext.getRequiredExtensions();
        inst_info.enabledExtensionCount = static_cast<uint32_t>(Ext.requiredExtensions.size());
        inst_info.ppEnabledExtensionNames = Ext.requiredExtensions.data();

        if (! enableValidationLayers)
        {
            inst_info.enabledLayerCount = 0;
            inst_info.ppEnabledLayerNames = NULL;
        }
        else
        {
            if (valLay.checkSupport())
            {
                inst_info.enabledLayerCount = static_cast<uint32_t>(valLay.requiredValidationLayers.size());
                inst_info.ppEnabledLayerNames = valLay.requiredValidationLayers.data();
            }
            else throw std::runtime_error("Validation Layers are not supported\n");
        }

        if (vkCreateInstance(&inst_info, NULL, &instance) == VK_ERROR_INCOMPATIBLE_DRIVER)
        {
            std::cout << "cannot find a compatible Vulkan ICD\n";
            exit(-1);
        }
        else std::cout << "Instance was created successfully\n";

    }
#pragma endregion

    void Loop()
    {
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
            drawFrame();
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                break;
        }
        vkDeviceWaitIdle(device);
    }

    void drawFrame() {
        vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

        uint32_t imageIndex;
        vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

        if (imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
            vkWaitForFences(device, 1, &imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
        }
        imagesInFlight[imageIndex] = inFlightFences[currentFrame];

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;

        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffers[imageIndex];

        VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        vkResetFences(device, 1, &inFlightFences[currentFrame]);

        if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = { swapChain };
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        vkQueuePresentKHR(presentationQueue, &presentInfo);


        currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    }

    void ClearUp()
    {
        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
            vkDestroyFence(device, inFlightFences[i], nullptr);
        }
        vkDestroyCommandPool(device, commandPool, nullptr);

        for (auto framebuffer : swapChainFramebuffers) {
            vkDestroyFramebuffer(device, framebuffer, nullptr);
        }
        vkDestroyPipeline(device, graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
        vkDestroyRenderPass(device, renderPass, nullptr);

        if (enableValidationLayers) {
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, NULL);
        }

        for (auto imageView : swapChainImageViews) {
            vkDestroyImageView(device, imageView, nullptr);
        }
        vkDestroySwapchainKHR(device, swapChain, nullptr);

        vkDestroyDevice(device, NULL);

        vkDestroySurfaceKHR(instance, surface, nullptr);

        vkDestroyInstance(instance, nullptr);

        std::cout << "Cleaning done";
    }
};


int main(int argc, char* argv[])
{
    VulkanProgram prog;
    prog.run();
}

