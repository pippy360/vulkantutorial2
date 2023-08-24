#pragma once
#include "lve_device.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace lve {

struct PipelineConfigInfo {
  VkViewport viewport;
  VkRect2D scissor;
  VkPipelineViewportStateCreateInfo viewportInfo;
  VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
  VkPipelineRasterizationStateCreateInfo rasterizationInfo;
  VkPipelineMultisampleStateCreateInfo multisampleInfo;
  VkPipelineColorBlendAttachmentState colorBlendAttachment;
  VkPipelineColorBlendStateCreateInfo colorBlendInfo;
  VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
  VkPipelineLayout pipelineLayout = nullptr;
  VkRenderPass renderPass = nullptr;
  uint32_t subpass = 0;
};


class LvePipeline {

public:
    LvePipeline(LveDevice& device,
                const PipelineConfigInfo& config,
                std::string vertFilePath,
                std::string fragFilePath): device_{device} {
        createGraphicsPipeline(config, vertFilePath, fragFilePath);
    }

    LvePipeline(const LvePipeline&) = delete;
    LvePipeline& operator=(LvePipeline&) = delete;

    ~LvePipeline();

    static PipelineConfigInfo defaultPipelineConfig(uint32_t width, uint32_t height);

private:

    void createGraphicsPipeline(const PipelineConfigInfo& config,
                std::string vertFilePath,
                std::string fragFilePath);

    void createShaderModule(const std::vector<char>& shaderCode,
                            VkShaderModule* module);

    LveDevice& device_;
    VkPipeline graphicsPipeline_;
    VkShaderModule fragShader_;
    VkShaderModule vertShader_;

};

} // end of lve
