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
#endif

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

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

    std::vector<VkLayerProperties> getLayers()
    {
        std::vector<VkLayerProperties> layers = utils::getData(vkEnumerateInstanceLayerProperties);
        return layers;
    }

}
namespace gpu
{
    void ListExtensions(VkPhysicalDevice device)
    {
        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(device, &properties);
        std::cout << "\t" << properties.deviceName << "\n";


        std::vector<VkExtensionProperties> extensions = wrappers::getExtensions(device);
        

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

    bool isGPUSuitable(VkPhysicalDevice device, std::vector<const char*> required_extensions)
    {
        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(device, &properties);


        std::vector<VkExtensionProperties> extensions = wrappers::getExtensions(device);


        for (auto req_extension : required_extensions)
        {
            bool found = false;
            for (auto extension : extensions)
            {
                std::cout << "\t\t" << extension.extensionName << "\n";
                if (!strcmp(req_extension, extension.extensionName))
                {
                    found = true;
                    break;
                }
            }

            if (!found)
                return false;
        }
        return true;
    }

    VkPhysicalDevice SelectGPU(VkInstance instance, std::vector<const char*> required_ext)
    {
        VkPhysicalDevice device = VK_NULL_HANDLE;

        std::vector<VkPhysicalDevice> gpus = wrappers::getGPUS(instance);

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
            if (isGPUSuitable(pair.first, required_ext))
            {
                device = pair.first;
                break;
            }
        }
            
        return device;
        
    }

    void doGPUOperation(VkInstance instance, void (*func)(VkPhysicalDevice device) = NULL)
    {
        
        std::vector<VkPhysicalDevice> gpus = wrappers::getGPUS(instance);

        if (func)
        {
            for (auto gpu : gpus)
            {
                func(gpu);
            }
        }
        
            
    }
}
namespace queuefamilies
{
    std::vector<VkQueueFamilyProperties> getQueueProperties(VkPhysicalDevice device)
    {
        std::vector<VkQueueFamilyProperties> Properties = utils::getData(device, vkGetPhysicalDeviceQueueFamilyProperties);
        return Properties;
    }
};

class Extensions
{
public:

    std::vector<const char*> requiredExtensions = { VK_EXT_DEBUG_UTILS_EXTENSION_NAME };

    Extensions() {};
    ~Extensions() {};

    void getRequiredExtensions()
    {
        uint32_t count;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&count);

        for (auto i = 0; i < count; i++)
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
                //std::cout << "\t" << layer.layerName << "\n";
                if (!strcmp(layer.layerName, required))
                {
                    found = true;
                    break;
                }

            }

            if (!found)
            {
                throw std::runtime_error("Could't find required extension");
                return false;

            }
        }
        return true;

    }

};


class VulkanProgram
{
public:

    VkInstance instance;
    Extensions Ext;
    ValidationLayers valLay;


    void run()
    {

        //initWindow();
        initVulkan();
        setupDebugMessenger();

        //gpu::doGPUOperation(instance, gpu::ListExtensions);

        std::vector<VkPhysicalDevice> gpus = wrappers::getGPUS(instance);


        // TEST ZONE
        //std::vector<VkPhysicalDevice> gpus = utils::getGPUS(instance);
        /* VULKAN_KEY_START */
        VkDeviceQueueCreateInfo queue_info = {};



        std::vector<VkQueueFamilyProperties> Qprop = queuefamilies::getQueueProperties(physicalDevice);
        
        bool found = false;
        for (unsigned int i = 0; i < Qprop.size(); i++) {
            if (Qprop[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                queue_info.queueFamilyIndex = i;
                found = true;
                break;
            }
        }

        float queue_priorities[1] = { 0.0 };
        queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_info.pNext = NULL;
        queue_info.queueCount = 1;
        queue_info.pQueuePriorities = queue_priorities;

        VkDeviceCreateInfo device_info = {};
        device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        device_info.pNext = NULL;
        device_info.queueCreateInfoCount = 1;
        device_info.pQueueCreateInfos = &queue_info;
        device_info.enabledExtensionCount = 0;
        device_info.ppEnabledExtensionNames = NULL;
        device_info.enabledLayerCount = 0;
        device_info.ppEnabledLayerNames = NULL;
        device_info.pEnabledFeatures = NULL;

        VkDevice device;
        if (vkCreateDevice(gpus[0], &device_info, NULL, &device) != VK_SUCCESS)
            throw std::runtime_error("Could't create device!");

        vkDestroyDevice(device, NULL);
        /* VULKAN_KEY_END */

        std::cout << "Sup\n";

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

#pragma region initVulkan

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

    void initVulkan()
    {
        std::cout << "Initializing the engine...\n";
        genInstance();
        physicalDevice = gpu::SelectGPU(instance, Ext.requiredExtensions);
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

    }

    void ClearUp()
    {
        if (enableValidationLayers) {
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, NULL);
        }

        vkDestroyInstance(instance, NULL);
        std::cout << "Cleaning done";
    }

};


int main(int argc, char* argv[])
{
    VulkanProgram prog;
    prog.run();
}

