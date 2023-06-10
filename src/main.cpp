
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "app/application.hpp"

#define WIDTH  1024
#define HEIGHT 720
#define TITLE  "Hello World!"

int main() {
    auto app = std::make_unique<Application>(TITLE, WIDTH, HEIGHT);
    return app->run();
}

