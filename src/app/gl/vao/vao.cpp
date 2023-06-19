#include "vao.hpp"
#include "common.h"
#include <memory>

using namespace ngl;


void VAO::link(std::unique_ptr<ngl::VBO> &buffer_object, GLuint layout, GLuint components_count, GLenum type, GLsizeiptr stride, void* offset) {
    glEnableVertexAttribArray(layout);
    buffer_object->bind();
    this->bind();

    glVertexAttribPointer(layout, components_count, type, GL_FALSE, stride, offset);
}

void VAO::unlink(std::unique_ptr<ngl::VBO> &buffer_object, GLuint layout) {
    buffer_object->unbind();
    this->unbind();
    glDisableVertexAttribArray(layout);
}

void VAO::bind() {
    glBindVertexArray(this->id);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::draw(GLenum mode, GLuint first, GLuint count, const GLvoid* indices) {
    this->bind();
    // glDrawArrays(mode, first, count);
    glDrawElements(mode, first, count, indices);
    this->unbind();
}

void VAO::destruct() {
    glDeleteVertexArrays(1, &this->id);
    this->valid = false;
}

bool VAO::is_valid() {
    bool old_state = this->valid;
    this->valid = glIsVertexArray(this->id);
    if (old_state && !this->valid) {
        if (this->valid) {
            err("VAO (%d) is now invalid", this->id);
        }
    }

    return this->valid;
}

