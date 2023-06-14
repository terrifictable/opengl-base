#pragma once

#include <GL/glew.h>


namespace ngl {
    class EBO {
    private:
        GLuint id;

    public:
        EBO(GLfloat* incdicies, GLsizeiptr size);
        ~EBO();

        void bind();
        void unbind();
        void destroy();
    };
}
