#include "ebo.hpp"


using namespace ngl;

EBO::EBO(GLfloat* indicies, GLsizeiptr size) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indicies, GL_STATIC_DRAW);
}

EBO::~EBO() {
    destroy();
}

void EBO::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void EBO::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::destroy() {
    glDeleteBuffers(1, &id);
}

