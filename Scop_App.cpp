//
// Created by Johannes Moritz on 09.07.25.
//

#include "Scop_App.hpp"

namespace scop {
void Scop_App::run() {
    while (!window.windowShouldClose()) {
        glfwPollEvents();
    }
}
} // namespace scop
