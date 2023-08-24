#include "game_window.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>
#include <stdexcept>

namespace lve {

const int kWindowHeight = 800;
const int kWindowWidth = 1000;


GameWindow::GameWindow(int w, int h, std::string name)
        : width_(w), height_(h), name_(name) {
    initWindow_();
}

void
GameWindow::initWindow_() {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWmonitor *monitor = nullptr;
    GLFWwindow *share = nullptr;
    window_ = glfwCreateWindow(kWindowWidth, kWindowHeight, "First window", monitor, share);
}

void
GameWindow::createWindowSurface(VkInstance &i, VkSurfaceKHR *s) {
    if (glfwCreateWindowSurface(i, window_, nullptr, s) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create surface");
    }
}

bool GameWindow::shouldClose() {
    return glfwWindowShouldClose(window_);
}

GameWindow::~GameWindow() {
    if (window_ != nullptr) {
        glfwDestroyWindow(window_);
    }
}

}
