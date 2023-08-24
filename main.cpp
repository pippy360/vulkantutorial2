#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "game_app.hpp"

using namespace lve;

int main() {
    glfwInit();

    GameApp app;
    app.run();

    glfwTerminate();
    return 0;
}