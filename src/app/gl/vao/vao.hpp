#pragma once

#include <GL/glew.h>
#include <memory>

#include "app/gl/vbo/vbo.hpp"

namespace ngl {
    class VAO {
    private:
        GLuint id;

    public:
        VAO();
        ~VAO();

        void link(std::unique_ptr<ngl::VBO> &buffer_object, GLuint layout, GLuint components_count, GLenum type, GLsizeiptr stride, void* offset);
        void unlink(std::unique_ptr<ngl::VBO> &buffer_object, GLuint layout);
        void bind();
        void unbind();
        void draw(GLenum mode, GLuint first, GLuint count);
        void destruct();
    };
}


