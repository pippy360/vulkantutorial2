#include "lve_pipeline.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace lve {


LvePipeline::~LvePipeline() {
    //FIXME: clean up here!!!
}

void
LvePipeline::createGraphicsPipeline(const PipelineConfigInfo& configInfo,
                                    std::string vertFilePath,
                                    std::string fragFilePath) {

    auto toCharVec = [](std::string filePath) {
        std::ifstream stream(filePath);
        std::stringstream shaderBuffer;
        shaderBuffer << stream.rdbuf();
        auto s = shaderBuffer.str();
        return std::vector<char>(s.begin(), s.end());
    };

    VkShaderModule vertShaderModule, fragShaderModule;
    createShaderModule(toCharVec(vertFilePath), &vertShaderModule);
    createShaderModule(toCharVec(fragFilePath), &fragShaderModule);

    VkPipelineShaderStageCreateInfo shaderStages[2] = {
        {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage = VK_SHADER_STAGE_VERTEX_BIT,
            .module = vertShaderModule,
            .pName = "main",
        },
        {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
            .module = vertShaderModule,
            .pName = "main",
        }
    };

    VkPipelineVertexInputStateCreateInfo vertexInfo {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .vertexAttributeDescriptionCount = 0,
    };

    VkGraphicsPipelineCreateInfo pipelineInfo {
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .stageCount = 2,
        .pStages = shaderStages,
        .pVertexInputState = &vertexInfo,
        .pInputAssemblyState = &configInfo.inputAssemblyInfo,
        .pViewportState = &configInfo.viewportInfo,
        .pRasterizationState = &configInfo.rasterizationInfo,
        .pColorBlendState = &configInfo.colorBlendInfo,
        .pDepthStencilState = &configInfo.depthStencilInfo,

        .layout = configInfo.pipelineLayout,
        .renderPass = configInfo.renderPass,
        .subpass = configInfo.subpass,

        .basePipelineIndex = -1,
        .basePipelineHandle = VK_NULL_HANDLE,
    };

    if (vkCreateGraphicsPipelines(device_.device(), VK_NULL_HANDLE, 1, &pipelineInfo,
                                  nullptr, &graphicsPipeline_) != VK_SUCCESS) {
        throw std::runtime_error("failed vkCreateGraphicsPipelines");
    }
}

void
LvePipeline::createShaderModule(const std::vector<char>& shaderCode,
                                VkShaderModule* shaderModule) {
    VkShaderModuleCreateInfo createInfo {
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .codeSize = shaderCode.size(),
        .pCode = reinterpret_cast<const uint32_t*>(shaderCode.data()),
    };

    if (vkCreateShaderModule(device_.device(), &createInfo, nullptr, shaderModule)) {
        throw std::runtime_error("Failed to create shader module.");
    }
}

PipelineConfigInfo
LvePipeline::defaultPipelineConfig(uint32_t width, uint32_t height) {

    PipelineConfigInfo configInfo = {
        .viewport = {
            .x = 0.0f,
            .y = 0.0f,
            .width = static_cast<float>(width),
            .height = static_cast<float>(height),
            .minDepth = 0.0f,
            .maxDepth = 1.0f,
        }, 
       
        .inputAssemblyInfo = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
            .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
            .primitiveRestartEnable = VK_FALSE,
        },

        .scissor = {
            .offset = {0, 0},
            .extent = {width, height},
        },
        
        .viewportInfo = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
            .viewportCount = 1,
            .pViewports = &configInfo.viewport,
            .scissorCount = 1,
            .pScissors = &configInfo.scissor,
        },
        
        .rasterizationInfo = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
            .depthClampEnable = VK_FALSE,
            .rasterizerDiscardEnable = VK_FALSE,
            .polygonMode = VK_POLYGON_MODE_FILL,
            .lineWidth = 1.0f,
            .cullMode = VK_CULL_MODE_NONE,
            .frontFace = VK_FRONT_FACE_CLOCKWISE,
            .depthBiasEnable = VK_FALSE,
            .depthBiasConstantFactor = 0.0f,  // Optional
            .depthBiasClamp = 0.0f,           // Optional
            .depthBiasSlopeFactor = 0.0f,     // Optional
        },
        
        //FIXME: write a UI to enable and disable multi sampling
        .multisampleInfo = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
            .sampleShadingEnable = VK_FALSE,
            .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
            .minSampleShading = 1.0f,           // Optional
            .pSampleMask = nullptr,             // Optional
            .alphaToCoverageEnable = VK_FALSE,  // Optional
            .alphaToOneEnable = VK_FALSE,       // Optional
        },
        
        .colorBlendAttachment = { 
            .colorWriteMask =
                VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT |
                VK_COLOR_COMPONENT_A_BIT,
            //FIXME: used for transparent!!
            .blendEnable = VK_FALSE,
            .srcColorBlendFactor = VK_BLEND_FACTOR_ONE,   // Optional
            .dstColorBlendFactor = VK_BLEND_FACTOR_ZERO,  // Optional
            .colorBlendOp = VK_BLEND_OP_ADD,              // Optional
            .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,   // Optional
            .dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,  // Optional
            .alphaBlendOp = VK_BLEND_OP_ADD,              // Optional
        },
        
        .colorBlendInfo = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
            .logicOpEnable = VK_FALSE,
            .logicOp = VK_LOGIC_OP_COPY,  // Optional
            .attachmentCount = 1,
            .pAttachments = &configInfo.colorBlendAttachment,
            .blendConstants[0] = 0.0f,  // Optional
            .blendConstants[1] = 0.0f,  // Optional
            .blendConstants[2] = 0.0f,  // Optional
            .blendConstants[3] = 0.0f,  // Optional
        },

        .depthStencilInfo = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
            .depthTestEnable = VK_TRUE,
            .depthWriteEnable = VK_TRUE,
            .depthCompareOp = VK_COMPARE_OP_LESS,
            .depthBoundsTestEnable = VK_FALSE,
            .minDepthBounds = 0.0f,  // Optional
            .maxDepthBounds = 1.0f,  // Optional
            .stencilTestEnable = VK_FALSE,
            .front = {},  // Optional
            .back = {},   // Optional
        }
    };

    return configInfo;
}

}

