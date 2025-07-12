#include "Scop_Window.hpp"

#include <utility>

namespace scop {
Scop_Window::Scop_Window(std::string name, const int width, const int height)
    : width(width),
      height(height),
      window_name(std::move(name)),
      window(nullptr) {
    init_window();
}

void Scop_Window::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
    if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create window surface");
    }
}

void Scop_Window::init_window() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr);
    if (!window) {
        throw std::runtime_error("Failed to create GLFW window");
    }
}

Scop_Window::~Scop_Window() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}
} // scop
