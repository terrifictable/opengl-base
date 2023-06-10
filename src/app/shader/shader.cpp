#include "shader.hpp"

#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <vector>

#include "common.h"



std::string read_file(const char* path, std::ios_base::openmode type) {
    std::ifstream stream(path, type);
    
    if (stream.is_open()) {
        std::stringstream sstr;
        sstr << stream.rdbuf();
        stream.close();
        return sstr.str();
    }

    return "\0";
}


GLuint load_shader(const char* vert_path, const char* frag_path) {
    GLuint vID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fID = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vert_code, frag_code;
    vert_code = read_file(vert_path, std::ios::in);
    if (vert_code == "\0") {
        err("Failed to read file: %s", curr, vert_path);
        return 0;
    }
    frag_code = read_file(frag_path, std::ios::in);
    if (vert_code == "\0") {
        err("Failed to read file: %s", curr, vert_path);
        return 0;
    }

    GLint status = GL_FALSE;
    GLint log_length = 0;


    dbg("Compiling shader: %s", vert_path);
    char const* vert_source_ptr = vert_code.c_str();
    glShaderSource(vID, 1, &vert_source_ptr, NULL);
    glCompileShader(vID);

    glGetShaderiv(vID, GL_COMPILE_STATUS, &status);
    glGetShaderiv(vID, GL_INFO_LOG_LENGTH, &log_length);
    if (status == 0) {
        char err_message[512];
        glGetShaderInfoLog(fID, log_length, NULL, err_message);
        err("Failed to compile vertex shader: %s", curr, err_message);
        return 1;
    }


    dbg("Compiling shader: %s", frag_path);
    char const* frag_source_ptr = frag_code.c_str();
    glShaderSource(fID, 1, &frag_source_ptr, NULL);
    glCompileShader(fID);

    glGetShaderiv(fID, GL_COMPILE_STATUS, &status);
    glGetShaderiv(fID, GL_INFO_LOG_LENGTH, &log_length);
    if (status == 0) {
        char err_message[512];
        glGetShaderInfoLog(fID, log_length, NULL, err_message);
        err("Failed to compile fragment shader: %s", curr, err_message);
        return 1;
    }

    
    dbg("%s", "Linking shaders to program");
    GLuint pID = glCreateProgram();
    glAttachShader(pID, vID);
    glAttachShader(pID, fID);
    glLinkProgram(pID);

    glGetShaderiv(pID, GL_LINK_STATUS, &status);
    glGetShaderiv(pID, GL_INFO_LOG_LENGTH, &log_length);
    if (status == 0) {
        char err_message[512];
        glGetShaderInfoLog(fID, log_length, NULL, err_message);
        err("Failed to link program: %s", curr, err_message);
        return 1;
    }

    glDetachShader(pID, vID);
    glDetachShader(pID, fID);

    glDeleteShader(vID);
    glDeleteShader(fID);

    return pID;
}

