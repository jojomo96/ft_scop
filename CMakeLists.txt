cmake_minimum_required(VERSION 3.31)
project(ft_scop)

include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

include_directories(/Users/moritzjo/VulkanSDK/1.4.313.1/macOS/include)
link_directories(/Users/moritzjo/VulkanSDK/1.4.313.1/macOS/lib)

set(CMAKE_CXX_STANDARD 20)

add_executable(ft_scop main.cpp
        Scop_Window.cpp
        Scop_Window.hpp
        Scop_App.cpp
        Scop_App.hpp
        Scope_Pipeline.cpp
        Scope_Pipeline.hpp
        Scop_Device.cpp
        Scop_Device.hpp
        Scop_Swap_Chain.cpp
        Scop_Swap_Chain.hpp)
target_link_libraries(ft_scop glfw vulkan)