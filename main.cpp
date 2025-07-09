#include <iostream>

#include "Scop_App.hpp"

int main() {
    scop::Scop_App app;

    try {
        app.run();
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
