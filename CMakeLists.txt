project(vulkanHelloWorld)
cmake_minimum_required(VERSION 3.10)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  " )
set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME}
                main.cpp
                game_app.cpp
                game_window.cpp
                lve_device.cpp
                lve_pipeline.cpp
            )

find_package(Vulkan REQUIRED)
find_package(glfw3 3.3 REQUIRED)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

if (VULKAN_FOUND)
    message(STATUS "Found Vulkan, Including and Linking now")
    include_directories(${Vulkan_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries (${PROJECT_NAME} ${Vulkan_LIBRARIES} glfw)
endif (VULKAN_FOUND)
