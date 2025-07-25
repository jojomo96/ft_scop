#ifndef SCOP_WINDOW_HPP
#define SCOP_WINDOW_HPP

#define GLFW_INCLUDE_VULKAN
#include <string>
#include <GLFW/glfw3.h>

namespace scop {
class Scop_Window {
public:
    Scop_Window(std::string name, int width, int height);

    ~Scop_Window();

    bool windowShouldClose() { return glfwWindowShouldClose(window); }

    void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

    VkExtent2D getExtent() {
        return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
    }

private:
    void init_window();

    const int width;
    const int height;

    std::string window_name;

    GLFWwindow *window;
};
} // scop

#endif //SCOP_WINDOW_HPP
