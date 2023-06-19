#pragma once

#include <GL/glew.h>


namespace ngl {
    class VBO {
    private:
        GLuint id;
        bool valid;
    
    public:
        VBO(GLfloat* verticies, GLsizeiptr size);
        ~VBO();

        void bind();
        void unbind();
        void destruct();

        bool is_valid();
    };
}

