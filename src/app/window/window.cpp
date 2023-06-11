#include "window.hpp"
#include <stdlib.h>

#include "GLFW/glfw3.h"
#include "common.h"
#include "app/shader/shader.hpp"


using namespace nwindow;

void GLWindow::init(const char* title, int width, int height) {
    glewExperimental = true;
    if (!glfwInit()) {
        err("Failed to initialize GLFW %s", curr, glfwGetVersionString());
        exit(0);
    }
    ok("Initialized GLFW %s", glfwGetVersionString());

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (mWindow == NULL) {
        err("%s", curr, "Failed to create window");
        glfwTerminate();
        exit(1);
    }
    dbg("%s", "Successfully created window");

    glfwMakeContextCurrent(mWindow);
    glfwSwapInterval(1);
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        err("Failed to initialize glew %s", curr, glewGetString(GLEW_VERSION));
        exit(1);
    }
    ok("Initialized glew %s", glewGetString(GLEW_VERSION));

    glfwSetInputMode(mWindow, GLFW_STICKY_KEYS, GL_TRUE);
}





static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     0.0f,  1.0f, 0.0f,
};


int GLWindow::pre_render_loop() {
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    state.vertexBuffer = vertexBuffer;

    state.programID = load_shader("shaders/vertex.glsl", "shaders/fragment.glsl");

    return 0;
}

void GLWindow::pre_render() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWindow::render() {
    glUseProgram(state.programID);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, state.vertexBuffer);
    glVertexAttribPointer(0 /* attribute */, 3 /* size */, GL_FLOAT /* type */, GL_FALSE /* normalized? */, 0 /* stride */, (void*)0 /* offset */);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);

    glUseProgram(0);
}

void GLWindow::post_render() {
    int display_w, display_h;
    glfwGetFramebufferSize(mWindow, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    glfwSwapBuffers(mWindow);
    glfwPollEvents();

    mIsRunning = glfwGetKey(mWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(mWindow) == 0;
}

int GLWindow::post_render_loop() {
    glDeleteProgram(state.programID);
    return 0;
}

