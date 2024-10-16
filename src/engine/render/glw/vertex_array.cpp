#include "../../sys.h"

namespace render {
    namespace glw {
        void VertexArray::init() {
            glGenVertexArrays(1, &this->id);
        }

        void VertexArray::release() {
            glDeleteVertexArrays(1, &this->id);
        }

        void VertexArray::bind() {
            glBindVertexArray(this->id);
        }

        void VertexArray::unbind() {
            glBindVertexArray(0);
        }

        void VertexArray::createAttrib(std::string name, uint32_t id) {
            this->attribs[name] = id;
        }

        void VertexArray::enable(std::string name) {
            glEnableVertexAttribArray(this->attribs.at(name));
        }

        void VertexArray::disable(std::string name) {
            glDisableVertexAttribArray(this->attribs.at(name));
        }

        void VertexArray::pointer(std::string name, GLint size, GLenum type) {
            glVertexAttribPointer(this->attribs.at(name), size, type, GL_FALSE, 0, nullptr);
        }

    }
}