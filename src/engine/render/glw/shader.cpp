#include "../../sys.h"

namespace render {
    namespace glw {
        void Shader::init(GLenum type, std::string path) {
            this->id = glCreateShader(type);

            // Load shader from file
            std::ifstream in(path);
            std::string contents;

            if(in.is_open()) {
                in.seekg(0, std::ios::end);
                contents.resize(in.tellg());
                in.seekg(0, std::ios::beg);
                in.read((char*)contents.data(), contents.size());
                in.close();
            }

            std::cout << contents << "\n";

            const char* c_src = contents.c_str();

            glShaderSource(this->id, 1, &c_src, nullptr);

            glCompileShader(this->id);

            // Check for errors
            int32_t len = 0;
            glGetShaderiv(this->id, GL_INFO_LOG_LENGTH, &len);

            if(len > 0) {
                std::string log;
                log.resize(len);
                glGetShaderInfoLog(this->id, log.size(), nullptr, (char*)log.data());
                std::cout << log << "\n";
                log.clear();
            }        
        }

        void Shader::release() {
            glDeleteShader(this->id);
        }
    }
}