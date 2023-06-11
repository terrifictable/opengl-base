#pragma once

#include <memory>

#include "app/imgui/imgui.hpp"
#include "window/window.hpp"

class Application {
private:
    static Application *sInstance;

    std::unique_ptr<nwindow::GLWindow> glWindow;
    std::unique_ptr<nimgui::Imgui> imgui;

public:
    Application(const char* name, int width, int height);  
    ~Application();

    static Application& Instance() { return *sInstance; };

    int run();
};

