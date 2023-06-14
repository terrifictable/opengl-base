#pragma once

#include <GL/glew.h>


namespace ngl {
    class VBO {
    private:
        GLuint id;
    
    public:
        VBO(GLfloat* verticies, GLsizeiptr size);
        ~VBO();

        void bind();
        void unbind();
        void destruct();
    };
}

