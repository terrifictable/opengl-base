#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace nwindow {
    typedef struct {
        int programID;
        GLuint vertexBuffer;
    } state_t;

    class GLWindow {
    private:
        GLFWwindow* mWindow;
        bool mIsRunning;

        state_t state;

    public:
        GLWindow() : mIsRunning(true) {}
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

