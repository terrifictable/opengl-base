#pragma once

#include <GL/glew.h>
#include <ios>

std::string read_file(const char* path, std::ios_base::openmode type);
GLuint load_shader(const char* vert_path, const char* frag_path);

