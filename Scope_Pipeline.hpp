//
// Created by Johannes Moritz on 09.07.25.
//

#ifndef SCOPE_PIPELINE_HPP
#define SCOPE_PIPELINE_HPP
#include <string>
#include <vector>

#include "Scop_Device.hpp"

namespace scop {
struct Pipeline_Config_Info {
    VkViewport viewport;
    VkRect2D scissor;
    VkPipelineViewportStateCreateInfo viewport_info;
    VkPipelineInputAssemblyStateCreateInfo input_assembly_info;
    VkPipelineRasterizationStateCreateInfo rasterization_info;
    VkPipelineMultisampleStateCreateInfo multisample_info;
    VkPipelineColorBlendAttachmentState color_blend_attachment;
    VkPipelineColorBlendStateCreateInfo color_blend_info;
    VkPipelineDepthStencilStateCreateInfo depth_stencil_info;
    VkPipelineLayout pipeline_layout = nullptr;
    VkRenderPass render_pass = nullptr;
    uint32_t subpass = 0;
};

class Scope_Pipeline {
public:
    Scope_Pipeline(
        Scop_Device &device,
        const std::string &vert_file_path,
        const std::string &frag_file_path,
        const Pipeline_Config_Info &config_info
    );

    ~Scope_Pipeline() = default;

    Scope_Pipeline(const Scope_Pipeline &) = delete;

    void operator=(const Scope_Pipeline &) = delete;

    static Pipeline_Config_Info default_pipeline_config_info(uint32_t width, uint32_t height);

private:
    static std::vector<char> read_file(const std::string &file_path);

    void create_graphics_pipeline(
        const std::string &vert_file_path,
        const std::string &frag_file_path,
        const Pipeline_Config_Info &config_info
    );

    void create_shader_modules(
        const std::vector<char> &code,
        VkShaderModule *shader_module
    );

    Scop_Device &scop_device;
    VkPipeline graphics_pipeline;
    VkShaderModule vert_shader_module;
    VkShaderModule frag_shader_module;
};
} // scope

#endif //SCOPE_PIPELINE_HPP
