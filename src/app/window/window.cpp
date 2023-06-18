#include "window.hpp"
#include <stdlib.h>

#include "GLFW/glfw3.h"
#include "app/gl/gl_utils.hpp"
#include "common.h"
#include "app/gl/shader/shader.hpp"


using namespace nwindow;

void GLWindow::errorCallback(int error, const char* description) {
    err("GLFW error callback:\n\terr: %d\n\tdescription: %s", error, description);
}

void GLWindow::init(const char* title, int width, int height) {
    glfwSetErrorCallback(errorCallback);

    glewExperimental = true;
    if (!glfwInit()) {
        err("Failed to initialize GLFW %s", glfwGetVersionString());
        exit(0);
    }
    ok("Initialized GLFW %s", glfwGetVersionString());

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    


    mWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (mWindow == NULL) {
        err("%s", "Failed to create window");
        glfwTerminate();
        exit(1);
    }
    dbg("%s", "Successfully created window");

    glfwMakeContextCurrent(mWindow);
    glfwSwapInterval(1);
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        err("Failed to initialize glew %s", glewGetString(GLEW_VERSION));
        exit(1);
    }
    ok("Initialized glew %s", glewGetString(GLEW_VERSION));
    
    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, (void*)nullptr);
    }


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
    state.vertexArray = std::make_unique<ngl::VAO>();
    state.vertexArray->bind();
    state.vertexBuffer = std::make_unique<ngl::VBO>((GLfloat*)g_vertex_buffer_data, sizeof(g_vertex_buffer_data));

    state.shader = std::make_unique<ngl::Shader>();
    state.shader->init("shaders/vertex.glsl", "shaders/fragment.glsl");

    glfwGetFramebufferSize(mWindow, &display_w, &display_h);
    return 0;
}

void GLWindow::pre_render() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWindow::render() {
    state.shader->use([&](GLuint id) {
        glUniform1f(glGetUniformLocation(id, "time"), glfwGetTime());
        glUniform2f(glGetUniformLocation(id, "resolution"), display_w, display_h);
    });

    state.vertexArray->link(state.vertexBuffer, 0, 3, GL_FLOAT, 0, (void*)0);
    state.vertexArray->draw(GL_TRIANGLES, 0, 3);
    state.vertexArray->unlink(state.vertexBuffer, 0);

    state.shader->finish();
}

void GLWindow::post_render() {
    glfwGetFramebufferSize(mWindow, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    glfwSwapBuffers(mWindow);
    glfwPollEvents();

    mIsRunning = glfwGetKey(mWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(mWindow) == 0;
}

int GLWindow::post_render_loop() {
    state.shader->destruct();
    state.vertexArray->destruct();
    state.vertexBuffer->destruct();
    return 0;
}

