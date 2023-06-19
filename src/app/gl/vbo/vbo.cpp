#include "vbo.hpp"
#include "common.h"

using namespace ngl;


VBO::VBO(GLfloat* verticies, GLsizeiptr size) {
    this->valid = false;
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
    this->valid = true;
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
    this->valid = false;
}

bool VBO::is_valid() {
    bool old_state = this->valid;
    this->valid = glIsBuffer(this->id);
    if (old_state && !this->valid) {
        err("VBO (%d) is now invalid", this->id);
    }

    return this->valid;
}

