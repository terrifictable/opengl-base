#include "application.hpp"
#include "app/imgui/imgui.hpp"

#include <memory>


Application::Application(const char* name, int width, int height) {
    glWindow = std::make_unique<nwindow::GLWindow>();
    glWindow->init(name, width, height);

    imgui = std::make_unique<nimgui::Imgui>();
    imgui->init(glWindow);
}

Application::~Application() {
    glfwTerminate();
}


int Application::run() {
    int status = imgui->pre_render_loop();
    if (status != 0) {
        return status;
    }
    status = glWindow->pre_render_loop();
    if (status != 0) {
        return status;
    }
    
    while (glWindow->is_running()) {
        glWindow->pre_render();
        imgui->pre_render();

        imgui->render();
        glWindow->render();
        
        imgui->post_render();
        glWindow->post_render();
    }


    status = imgui->post_render_loop();
    if (status != 0) {
        return status;
    }
    return glWindow->post_render_loop();
}

