#pragma once


#include <GL/glew.h>
#include "GLFW/glfw3.h"

#include <memory>
#include <stdio.h>
#include <stdlib.h>


namespace ngl {
    void getErrorByCode(char** dst, GLenum code);

    GLenum _glCheckError(const char* file, int line, const char* function);
    #define glCheckError() ngl::_glCheckError(curr);
 
}

void APIENTRY glDebugOutput(
        GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar *message,
        const void *userParam);

