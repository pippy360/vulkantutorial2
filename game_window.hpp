#pragma once

#include <string>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace lve {

class GameWindow {

public:
    GameWindow(int w=1000, int h=800, std::string name="");

    GameWindow(const GameWindow &) = delete;
    GameWindow& operator=(GameWindow &) = delete;

    ~GameWindow();

    void createWindowSurface(VkInstance &i, VkSurfaceKHR *s);
    bool shouldClose();

private:
    void initWindow_();
    int width_;
    int height_;
    std::string name_;
    GLFWwindow* window_{nullptr};
};

}