#include "gl_utils.hpp"

#include "common.h"
#include <string.h>


void ngl::getErrorByCode(char** dst, GLenum code) {
    char* error;
    switch (code) {
        case GL_INVALID_ENUM:                   error = (char*)"INVALID_ENUM"; break;
        case GL_INVALID_VALUE:                  error = (char*)"INVALID_VALUE"; break;
        case GL_INVALID_OPERATION:              error = (char*)"INVALID_OPERATION"; break;
        case GL_INVALID_INDEX:                  error = (char*)"INVALID_INDEX"; break;
        case GL_STACK_OVERFLOW:                 error = (char*)"STACK_OVERFLOW"; break;
        case GL_STACK_UNDERFLOW:                error = (char*)"STACK_UNDERFLOW"; break;
        case GL_OUT_OF_MEMORY:                  error = (char*)"OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:  error = (char*)"INVALID_FRAMEBUFFER_OPERATION"; break;
    }
    *dst = (char*)malloc(sizeof(char) * (strlen(error)+1));
    *dst = error;
}


GLenum ngl::_glCheckError(const char* file, int line, const char* function) {
    GLenum code;
    char* error;
    while ((code = glGetError()) != GL_NO_ERROR) {
        ngl::getErrorByCode(&error, code);

        _err("OpenGL Error: %s", file, line, function, error);
    }
    // causes segfault for me reason
    // free(error);

    return code;
}

// 'void (*)(unsigned int, unsigned int, unsigned int, unsigned int, int, const char*, const char*) 
// 'void (*)(unsigned int, unsigned int, unsigned int, unsigned int, int, const char*, const void*)

void APIENTRY glDebugOutput(
        GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar *message,
        const void *userParam) {
    (void)length;
    (void)userParam;

    char* source_msg;
    switch (source) {
        case GL_DEBUG_SOURCE_API:               source_msg = (char*)"API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:     source_msg = (char*)"Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:   source_msg = (char*)"Shader Compilation"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:       source_msg = (char*)"Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:       source_msg = (char*)"Application"; break;
        case GL_DEBUG_SOURCE_OTHER:             source_msg = (char*)"Other"; break;
    }

    char* type_msg;
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:               type_msg = (char*)"Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: type_msg = (char*)"Deprecated Behavior"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  type_msg = (char*)"Undefined Behavior"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         type_msg = (char*)"Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         type_msg = (char*)"Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              type_msg = (char*)"Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          type_msg = (char*)"Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           type_msg = (char*)"Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               type_msg = (char*)"Other"; break;
    }

    char* severity_msg;
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:         severity_msg = (char*)"High"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       severity_msg = (char*)"Medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          severity_msg = (char*)"Low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: severity_msg = (char*)"Notification"; break;
    }

    if (type == GL_DEBUG_TYPE_ERROR) {
        err("%s", "-----");
        err("Debug Message: (%d) %s", id, message);
        err("Source: %s", source_msg);
        err("Type: %s", type_msg);
        err("Severity: %s", severity_msg);
    } else {
        warn("%s", "-----");
        warn("Debug Message: (%d) %s", id, message);
        warn("Source: %s", source_msg);
        warn("Type: %s", type_msg);
        warn("Severity: %s", severity_msg);
    }
}

