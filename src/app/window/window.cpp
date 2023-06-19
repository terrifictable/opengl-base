#include "window.hpp"
#include <stdlib.h>
#include <string.h>

#include "GLFW/glfw3.h"
#include "app/gl/ebo/ebo.hpp"
#include "app/gl/gl_utils.hpp"
#include "app/storage.hpp"
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
     // 0.0f,  1.0f, 0.0f,
     /* need ebo for rectange */
      1.0f,  1.0f, 0.0f,
     -1.0f,  1.0f, 0.0f,
};

static const GLuint indices[] = {
    0, 1, 3,
    1, 2, 3
};


int GLWindow::pre_render_loop() {
    state.vertexArray = std::make_unique<ngl::VAO>();
    state.vertexArray->bind();
    state.vertexBuffer = std::make_unique<ngl::VBO>((GLfloat*)g_vertex_buffer_data, sizeof(g_vertex_buffer_data));

    ngl::EBO ebo((GLuint*)indices, sizeof(indices));
    state.vertexArray->link(state.vertexBuffer, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    state.vertexArray->link(state.vertexBuffer, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    state.vertexArray->unbind();
    state.vertexBuffer->unbind();
    ebo.unbind();


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
    if (glfwGetKey(mWindow, GLFW_KEY_F3) == GLFW_PRESS) { // reload shader
        state.shader->init("shaders/vertex.glsl", "shaders/fragment.glsl");
    }

    if (state.shader->is_valid()) {
        state.shader->use([&](GLuint id) {
                glUniform1f(glGetUniformLocation(id, "time"), glfwGetTime());
                glUniform2f(glGetUniformLocation(id, "resolution"), display_w, display_h);

                int size = strlen(g_data.str);
                int int_arr[256];
                for (int i=0; i < (int)sizeof(g_data.str) - 1 && i < size; i++) {
                    int_arr[i] = g_data.str[i];
                }

                if (g_data.centered) {
                    g_data.text_x = -1;
                    g_data.text_y = -1;
                }

                glUniform1i(glGetUniformLocation(id, "u_size"), size);
                glUniform1iv(glGetUniformLocation(id, "u_data"), 256, int_arr);
                glUniform1f(glGetUniformLocation(id, "u_anim_strength"), g_data.anim_strength);
                glUniform2f(glGetUniformLocation(id, "u_text_pos"), g_data.text_x, g_data.text_y);
        });

        if (state.vertexArray->is_valid() && state.vertexBuffer->is_valid()) {
            state.vertexArray->link(state.vertexBuffer, 0, 3, GL_FLOAT, 0 * sizeof(float), (void*)0);
            state.vertexArray->link(state.vertexBuffer, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
            state.vertexArray->draw(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            state.vertexArray->unlink(state.vertexBuffer, 0);
        } else {
            warn("%s", "vertexArray or vertexBuffer is invalid");
        }
 
        state.shader->finish();
    } else {
        warn("%s", "shader is invalid");
    }
}

void GLWindow::post_render() {
    glfwGetFramebufferSize(mWindow, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    g_data.display_w = display_w;
    g_data.display_h = display_h;

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

