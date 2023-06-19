#pragma once

#include <GL/glew.h>
#include <memory>

#include "app/gl/vbo/vbo.hpp"

namespace ngl {
    class VAO {
    private:
        GLuint id;
        bool valid;


    public:
        VAO() : valid(false) {
            glGenVertexArrays(1, &id);
            this->valid = true;
        }
        ~VAO() {
            this->destruct();
        }

        void link(std::unique_ptr<ngl::VBO> &buffer_object, GLuint layout, GLuint components_count, GLenum type, GLsizeiptr stride, void* offset);
        void unlink(std::unique_ptr<ngl::VBO> &buffer_object, GLuint layout);
        void bind();
        void unbind();
        // void draw(GLenum mode, GLuint first, GLuint count);
        void draw(GLenum mode, GLuint first, GLuint count, const GLvoid* indices);
        void destruct();

        bool is_valid();
    };
}


