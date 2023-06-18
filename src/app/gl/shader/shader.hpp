#pragma once

#include <GL/glew.h>
#include <functional>
#include <ios>

std::string read_file(const char* path, std::ios_base::openmode type);
// GLuint load_shader(const char* vert_path, const char* frag_path);

namespace ngl {
    // TODO: 
    class Shader {
    private:
        GLuint id;   

    public:
        Shader();
        ~Shader();

        void init(const char* vert_path, const char* frag_path);
        void use(std::function<void(GLuint)> const& lambda);
        void use();
        void finish();
        void destruct();
    };
}


