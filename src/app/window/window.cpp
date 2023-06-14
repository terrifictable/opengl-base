#include "window.hpp"
#include <stdlib.h>

#include "GLFW/glfw3.h"
#include "common.h"
#include "app/gl/shader/shader.hpp"


using namespace nwindow;

void GLWindow::errorCallback(int error, const char* description) {
    err("GLFW error callback:\n\terr: %d\n\tdescription: %s", curr, error, description);
}

void GLWindow::init(const char* title, int width, int height) {
    glfwSetErrorCallback(errorCallback);

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
     /* need ebo for rectange */
     // 1.0f,  1.0f, 0.0f,
     //-1.0f,  1.0f, 0.0f,
};


int GLWindow::pre_render_loop() {
    // state.vertexArray = std::make_unique<ngl::VAO>();
    // state.vertexArray->bind();
    // state.vertexBuffer = std::make_unique<ngl::VBO>((GLfloat*)g_vertex_buffer_data, sizeof(g_vertex_buffer_data));
    
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    state.vertexBuffer = vertexBuffer;


    state.programID = load_shader("shaders/vertex.glsl", "shaders/fragment.glsl");

    glfwGetFramebufferSize(mWindow, &display_w, &display_h);
    return 0;
}

void GLWindow::pre_render() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWindow::render() {
    // glUniform1f(glGetUniformLocation(state.programID, "time"), glfwGetTime());
    // glUniform2f(glGetUniformLocation(state.programID, "resolution"), display_w, display_h);
    glUseProgram(state.programID);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, state.vertexBuffer);
    glVertexAttribPointer(0 /* attribute */, 3 /* size */, GL_FLOAT /* type */, GL_FALSE /* normalized? */, 0 /* stride */, (void*)0 /* offset */);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);

    glUseProgram(0);
}

void GLWindow::post_render() {
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

