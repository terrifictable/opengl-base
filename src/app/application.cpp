#include "application.hpp"

#include <memory>


Application::Application(const char* name, int width, int height) {
    glWindow = std::make_unique<nwindow::GLWindow>();
    glWindow->init(name, width, height);
}

Application::~Application() {
    glfwTerminate();
}


int Application::run() {
    int status = glWindow->pre_render();
    if (status != 0) {
        return status;
    }
    
    while (glWindow->is_running()) {
        glWindow->render();
    }

    return glWindow->post_render();
}

