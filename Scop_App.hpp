#ifndef SCOP_APP_HPP
#define SCOP_APP_HPP
#include "Scope_Pipeline.hpp"
#include "Scop_Window.hpp"
#include "Scop_Device.hpp"


namespace scop {
class Scop_App {
public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    void run();

private:
    Scop_Window window{"Scop Application", WIDTH, HEIGHT};
    Scop_Device device{window};
    Scope_Pipeline pipeline{
        device,
        "../shaders/simple_shader.vert.spv",
        "../shaders/simple_shader.frag.spv",
        Scope_Pipeline::default_pipeline_config_info(WIDTH, HEIGHT)
    };
};
}

#endif //SCOP_APP_HPP
