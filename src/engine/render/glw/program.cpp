#include "../../sys.h"
#include <algorithm>


namespace render {
    namespace glw {
        void Program::init(const std::vector<Shader*>& shaders) {
            this->id = glCreateProgram();

            std::for_each(shaders.begin(), shaders.end(), [&](Shader* shader) {
                glAttachShader(this->id, shader->id);
                this->shaders.push_back(shader);
            });

            glLinkProgram(this->id);

            int32_t len = 0;

            glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &len);

            if(len > 0) {
                std::string log;
                log.resize(len);
                //glGetShaderInfoLog(temp, log.size(), nullptr, (char*)log.data());
                glGetProgramInfoLog(this->id, log.size(), nullptr, (char*)log.data());
                std::cout << log << "\n";
                log.clear();
            }


            // VertexArray
            this->vertexArray.init();
            
            // Uniform
            this->uniform.init(this);
        }

        void Program::release() {
            this->uniform.release();
            this->vertexArray.release();
            
            std::for_each(this->shaders.begin(), this->shaders.end(), [&](Shader* shader) {
                glDetachShader(this->id, shader->id);
            });

            this->shaders.clear();

            glDeleteProgram(this->id);
        }

        void Program::bind() {
            glUseProgram(this->id);
        }

        void Program::unbind() {
            glUseProgram(0);
        }

    }
}