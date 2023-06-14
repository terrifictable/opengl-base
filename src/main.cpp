#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "app/application.hpp"

#define WIDTH  1280
#define HEIGHT 720

int main() {
    auto app = std::make_unique<Application>("OpenGL Base", WIDTH, HEIGHT);
    return app->run();
}

