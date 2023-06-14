#include "vbo.hpp"

using namespace ngl;


VBO::VBO(GLfloat* verticies, GLsizeiptr size) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
}
VBO::~VBO() {
    destruct();
}


void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::destruct() {
    glDeleteBuffers(1, &id);
}

