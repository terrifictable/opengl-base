/* filename cuz problems with library names */

#include "app/storage.hpp"
#include "imgui.hpp"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "roboto.h"

using namespace nimgui;


Imgui::~Imgui() {}


void Imgui::init(std::unique_ptr<nwindow::GLWindow> &window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); (void)io;
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    io->Fonts->AddFontDefault();
    ImFont* font = io->Fonts->AddFontFromMemoryCompressedTTF(roboto_compressed_data, roboto_compressed_size, 15);
    assert(font != nullptr && "Failed to load roboto font");
    io->FontDefault = font;

    ImGui::StyleColorsDark();

    style = &ImGui::GetStyle();
    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style->Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(window->get_native_window(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    
}

int Imgui::pre_render_loop(){
    return 0;
}



void Imgui::pre_render(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Imgui::render() {
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

    ImGui::Checkbox("Centered", &g_data.centered);
    if (!g_data.centered) {
        ImGui::SliderFloat("Text X", &g_data.text_x, 0, g_data.display_w / 2.);
        ImGui::SliderFloat("Text Y", &g_data.text_y, 0, g_data.display_h / 2. - 10.);
    }
    ImGui::SliderFloat("Animation Strength", &g_data.anim_strength, -1.0f, 15.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

    ImGui::InputTextMultiline("Text", g_data.str, 256);
    // strrep(g_data.str, '\n', (char)nl);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
}

void Imgui::post_render(){
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}



int Imgui::post_render_loop(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    return 0;
}

