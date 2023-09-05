#pragma once

#include "lve_pipeline.hpp"
#include "lve_window.hpp"
#include "lve_swap_chain.hpp"

namespace lve {
class FirstApp {
 public:
  static constexpr int WIDTH = 800;
  static constexpr int HEIGHT = 600;

  FirstApp() {
      createPipelineLayout();
      createPipeline();
      createCommandBuffers();
  };

  void run();
  void createCommandBuffers();
  void drawFrame();

 private:

  void createPipelineLayout();
  void createPipeline();

    //FIXME: here is why you'd want to have a builder!!!
  LveWindow lveWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
  LveDevice lveDevice{lveWindow};
  VkPipelineLayout pipelineLayout;
  LveSwapChain lveSwapChain{lveDevice, lveWindow.getExtent()};
  std::unique_ptr<LvePipeline> lvePipeline;
  std::vector<VkCommandBuffer> commandBuffers;
};
}  // namespace lve