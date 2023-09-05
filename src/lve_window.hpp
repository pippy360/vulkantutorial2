#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>
namespace lve {

class LveWindow {
 public:
  LveWindow(uint32_t w, uint32_t h, std::string name);
  ~LveWindow();

  LveWindow(const LveWindow &) = delete;
  LveWindow &operator=(const LveWindow &) = delete;

  bool shouldClose() { return glfwWindowShouldClose(window); }

  void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

  int getWidth() { return width; }
  int getHeight() { return height; }
  VkExtent2D getExtent() { return {width, height}; };

 private:
  void initWindow();

  const uint32_t width;
  const uint32_t height;

  std::string windowName;
  GLFWwindow *window;
};
}  // namespace lve
