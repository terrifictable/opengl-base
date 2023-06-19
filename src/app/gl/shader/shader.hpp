#pragma once

#include <GL/glew.h>
#include <functional>
#include <ios>

std::string read_file(const char* path, std::ios_base::openmode type);

namespace ngl {
    class Shader {
    private:
        GLuint id;   
        bool valid;

    public:
        Shader() : valid(true) {}
        ~Shader() {
            this->destruct();
        }

        void init(const char* vert_path, const char* frag_path);
        void use(std::function<void(GLuint)> const& lambda);
        void use();
        void finish();
        void destruct();

        bool is_valid();
    };
}


