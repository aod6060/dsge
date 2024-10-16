#include "../../sys.h"

namespace render {
    namespace glw {
        void Uniform::init(Program* program) {
            this->program = program;
        }

        void Uniform::release() {
            program = nullptr;
        }

        void Uniform::createUniform(std::string name) {
            this->uniforms[name] = glGetUniformLocation(program->id, name.c_str());
        }

        // Integers
        void Uniform::set1i(std::string name, int x) {
            glUniform1i(this->uniforms.at(name), x);
        }

        void Uniform::set2i(std::string name, int x, int y) {
            glUniform2i(this->uniforms.at(name), x, y);
        }

        void Uniform::set3i(std::string name, int x, int y, int z) {
            glUniform3i(this->uniforms.at(name), x, y, z);
        }

        void Uniform::set4i(std::string name, int x, int y, int z, int w) {
            glUniform4i(this->uniforms.at(name), x, y, z, w);
        }

        // Floats
        void Uniform::set1f(std::string name, float x) {
            glUniform1f(this->uniforms.at(name), x);
        }

        void Uniform::set2f(std::string name, float x, float y) {
            glUniform2f(this->uniforms.at(name), x, y);
        }

        void Uniform::set3f(std::string name, float x, float y, float z) {
            glUniform3f(this->uniforms.at(name), x, y, z);
        }

        void Uniform::set4f(std::string name, float x, float y, float z, float w) {
            glUniform4f(this->uniforms.at(name), x, y, z, w);
        }

        // Matrix
        void Uniform::setMatrix2(std::string name, const glm::mat2& m) {
            glUniformMatrix2fv(this->uniforms.at(name), 1, GL_FALSE, &m[0][0]);
        }

        void Uniform::setMatrix3(std::string name, const glm::mat3& m) {
            glUniformMatrix3fv(this->uniforms.at(name), 1, GL_FALSE, &m[0][0]);
        }

        void Uniform::setMatrix4(std::string name, const glm::mat4& m) {
            glUniformMatrix4fv(this->uniforms.at(name), 1, GL_FALSE, &m[0][0]);
        }

    }
}