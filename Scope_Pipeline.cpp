//
// Created by Johannes Moritz on 09.07.25.
//

#include "Scope_Pipeline.hpp"

#include <fstream>
#include <iostream>

namespace scop {
Scope_Pipeline::Scope_Pipeline(
    Scop_Device &device,
    const std::string &vert_file_path,
    const std::string &frag_file_path,
    const Pipeline_Config_Info &config_info
) : scop_device(device) {
    create_graphics_pipeline(vert_file_path, frag_file_path, config_info);
}

Pipeline_Config_Info Scope_Pipeline::default_pipeline_config_info(
    uint32_t width,
    uint32_t height
) {
    Pipeline_Config_Info config_info;

    return config_info;
}

std::vector<char> Scope_Pipeline::read_file(
    const std::string &file_path
) {
    std::ifstream file(file_path, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + file_path);
    }

    size_t file_size = file.tellg();
    std::vector<char> buffer(file_size);

    file.seekg(0);
    file.read(buffer.data(), file_size);

    file.close();
    return buffer;
}

void Scope_Pipeline::create_graphics_pipeline(
    const std::string &vert_file_path,
    const std::string &frag_file_path,
    const Pipeline_Config_Info &config_info
) {
    auto vert_code = read_file(vert_file_path);
    auto frag_code = read_file(frag_file_path);

    std::cout << "Vertex shader code size: " << vert_code.size() << " bytes" << std::endl;
    std::cout << "Fragment shader code size: " << frag_code.size() << " bytes" << std::endl;
}

void Scope_Pipeline::create_shader_modules(
    const std::vector<char> &code,
    VkShaderModule *shader_module
) {
    VkShaderModuleCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    create_info.codeSize = code.size();
    create_info.pCode = reinterpret_cast<const uint32_t *>(code.data());

    if (vkCreateShaderModule(scop_device.device(), &create_info, nullptr, shader_module) != VK_SUCCESS) {
        throw std::runtime_error("failed to create shader module!");
    }
}
} // scope
