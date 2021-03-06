cmake_minimum_required(VERSION 3.10)

# set the project name
project("VULKAN_Tests")

set_property (DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})



option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(Dependencies/vendor/glfw)


find_package(Vulkan REQUIRED)
#target_compile_definitions(${PROJECT_NAME} PRIVATE VK_USE_PLATFORM_WIN32_KHR)



if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    set(CMAKE_CXX_STANDARD 17)
    set(VK_LAYER_PATH C:/VulkanSDK/1.2.148.1/Bin)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE )  # poti sa folosesti si functii nesigure (ex fopen)

else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++17 -O2  -lglfw -lvulkan -ldl -lpthread")
    if(NOT WIN32)
        #set(GLAD_LIBRARIES g dl GL GLU glfw X11 Xxf86vm Xrandr pthread Xi Xinerama Xcursor assimp)
    endif()
endif()


# add include
include_directories(Dependencies/include/
					Dependencies/vendor/glfw/include
					Dependencies/vendor/glm/glm
					)

# add sources
file(GLOB PROJECT_SOURCES Dependencies/src/*.cpp Dependencies/src/*.c)
file(GLOB PROJECT_HEADERS Dependencies/include/*)
file(GLOB PROJECT_SHADERS
		Dependencies/shaders/*.glsl)
file(GLOB PROJECT_GEOMETRY_SHADERS
		Dependencies/shaders/geometry/*.glsl)


source_group("shaders" FILES ${PROJECT_SHADERS})
source_group("imgui"   FILES ${IMGUI})

add_definitions(-DGLFW_INCLUDE_NONE -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

# add the executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
									 ${PROJECT_SHADERS})


target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} Vulkan::Vulkan)


set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
