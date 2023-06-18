#include "application.hpp"
#include "app/imgui/imgui.hpp"
#include "common.h"

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
        err("imgui->pre_render_loop returned non 0 value: %d", status);
        return status;
    }

    status = glWindow->pre_render_loop();
    if (status != 0) {
        err("glWindow->pre_render_loop returned non 0 value: %d", status);
        return status;
    }
    

    while (glWindow->is_running()) {
#ifdef RENDER_DBG
        dbg("%s", "glWindow->pre_render");
        glWindow->pre_render();
        dbg("%s", "imgui->pre_render");
        imgui->pre_render();

        dbg("%s", "imgui->render");
        imgui->render();
        dbg("%s", "glWindow->render");
        glWindow->render();
        
        dbg("%s", "imgui->post_render");
        imgui->post_render();
        dbg("%s", "glWindow->post_render");
        glWindow->post_render();
#else
        glWindow->pre_render();
        imgui->pre_render();

        imgui->render();
        glWindow->render();
        
        imgui->post_render();
        glWindow->post_render();
#endif
    }


    status = imgui->post_render_loop();
    if (status != 0) {
        err("imgui->post_render_loop returned non 0 value: %d", status);
        return status;
    }
    status = glWindow->post_render_loop();
    if (status != 0) {
        err("glWindow->post_render_loop returned non 0 value: %d", status);
        return status;
    }
    return 0;
}

