#include "first_app.hpp"

namespace lve {

void FirstApp::run() {
  createCommandBuffers();
  while (!lveWindow.shouldClose()) {
    glfwPollEvents();
    drawFrame();
  }
}

void
FirstApp::createPipelineLayout() {
  VkPipelineLayoutCreateInfo info{
    .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
    .setLayoutCount = 0,
    .pSetLayouts = nullptr,
    .pushConstantRangeCount = 0,
    .pPushConstantRanges = nullptr
  };
  VkPipelineLayout layout;
  //FIXME: not cleaned up!!!
  if (vkCreatePipelineLayout(lveDevice.device(), &info, nullptr, &pipelineLayout) != VK_SUCCESS) {
    throw std::runtime_error("create pipeline failed");
  }
}

void FirstApp::createPipeline() {
  auto pipelineConfig =
      LvePipeline::defaultPipelineConfigInfo(lveSwapChain.width(), lveSwapChain.height());
  pipelineConfig.renderPass = lveSwapChain.getRenderPass();
  pipelineConfig.pipelineLayout = pipelineLayout;
  lvePipeline = std::make_unique<LvePipeline>(
      lveDevice,
      "/Users/tomnom/git/vulkantutorial2/shaders/simple_shader.vert.spv",
      "/Users/tomnom/git/vulkantutorial2/shaders/simple_shader.frag.spv",
      pipelineConfig);
}

void
FirstApp::createCommandBuffers() {
  commandBuffers.resize(lveSwapChain.imageCount());

  VkCommandBufferAllocateInfo allocInfo {
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
    .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
    .commandPool = lveDevice.getCommandPool(),
    .commandBufferCount = static_cast<uint32_t>(commandBuffers.size()),
  };

  if (vkAllocateCommandBuffers(lveDevice.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
    throw std::runtime_error("failed to alloc command buffers");
  }

  for (int i = 0; i < commandBuffers.size(); i++) {
    auto& cb = commandBuffers[i];
    VkCommandBufferBeginInfo info {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO
    };

    if (vkBeginCommandBuffer(cb, &info) != VK_SUCCESS) {
      throw std::runtime_error("failed to begin command buffer");
    }

    VkRenderPassBeginInfo renderPassInfo {
      .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
      .renderPass = lveSwapChain.getRenderPass(),
      .framebuffer = lveSwapChain.getFrameBuffer(i),
      .renderArea {
        .offset{0, 0},
        .extent{lveSwapChain.getSwapChainExtent()}
      },
    };

    std::array<VkClearValue, 2> clearValues {
      VkClearValue {
        .color = {0.1f, 0.1f, 0.1f, 0.1f}
      },
      VkClearValue {
        .depthStencil = {1.0f, 0}
      }
    };
    renderPassInfo.clearValueCount = clearValues.size();
    renderPassInfo.pClearValues = clearValues.data();
    
    vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    lvePipeline->bind(commandBuffers[i]);

    vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);
    vkCmdEndRenderPass(commandBuffers[i]);

    if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
      throw std::runtime_error("failed to record command buffer");
    }
  }
}

void
FirstApp::drawFrame() {
  uint32_t imageIndex;
  auto result = lveSwapChain.acquireNextImage(&imageIndex);
  if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
    throw std::runtime_error("failed to aquire swapchain image");
  }

  result = lveSwapChain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
}


}  // namespace lve