#pragma once


#include <memory>

#include <imgui/imgui.h>

#include "app/window/window.hpp"


namespace nimgui {
    class Imgui {
    private:
        ImGuiIO* io;
        bool show_demo_window = false;

    public:
        Imgui() {
        }
        ~Imgui();

        void init(std::unique_ptr<nwindow::GLWindow> &window);

        int pre_render_loop();
        void pre_render();
        void render();
        void post_render();
        int post_render_loop();
    };
}

