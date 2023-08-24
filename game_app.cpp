#include "game_app.hpp"
#define GLFW_INCLUDE_VULKAN

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace lve {

GameApp::GameApp() {
}

void
GameApp::run() {

    while(!window_.shouldClose()) {
        glfwPollEvents();
    }

}

GameApp::~GameApp() {
}

} // end of lve

