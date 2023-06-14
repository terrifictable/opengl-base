#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>


namespace nwindow {
    typedef struct {
        int programID;
        // std::unique_ptr<ngl::VBO> vertexBuffer;
        // std::unique_ptr<ngl::VAO> vertexArray;
        GLuint vertexBuffer;
    } state_t;

    class GLWindow {
    private:
        GLFWwindow* mWindow;
        int display_w, display_h;
        bool mIsRunning;

        state_t state;

        static void errorCallback(int error, const char* description);

    public:
        GLWindow() {}
        ~GLWindow() {}

        void init(const char* title, int width, int height);

        bool is_running() { return mIsRunning; };

        void set_native_window(void* window) { mWindow = (GLFWwindow*)window; }
        GLFWwindow* get_native_window()      { return mWindow; }

        int pre_render_loop();
        void pre_render();
        void render();
        void post_render();
        int post_render_loop();
    };
}

