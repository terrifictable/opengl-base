#include "vao.hpp"
#include <memory>

using namespace ngl;


VAO::VAO() {
    glGenVertexArrays(1, &id);
}
VAO::~VAO() {
    destruct();
}


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
    glBindVertexArray(id);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::draw(GLenum mode, GLuint first, GLuint count) {
    bind();
    glDrawArrays(mode, first, count);
    unbind();
}

void VAO::destruct() {
    glDeleteVertexArrays(1, &id);
}

