#include "../../sys.h"

namespace render {
    namespace glw {
        void IndexBuffer::add1(int x) {
            this->list.push_back(x);
        }

        void IndexBuffer::add2(int x, int y) {
            this->list.push_back(x);
            this->list.push_back(y);
        }

        void IndexBuffer::add3(int x, int y, int z) {
            this->list.push_back(x);
            this->list.push_back(y);
            this->list.push_back(z);
        }

        void IndexBuffer::add4(int x, int y, int z, int w) {
            this->list.push_back(x);
            this->list.push_back(y);
            this->list.push_back(z);
            this->list.push_back(w);
        }

        void IndexBuffer::clear() {
            this->list.clear();
        }

        void IndexBuffer::init() {
            glGenBuffers(1, &this->id);
        }

        void IndexBuffer::release() {
            glDeleteBuffers(1, &this->id);
        }

        void IndexBuffer::update() {
            this->bind();
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->dataSize(), this->list.data(), GL_DYNAMIC_DRAW);
            this->unbind();
        }

        void IndexBuffer::bind() {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
        }

        void IndexBuffer::unbind() {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        size_t IndexBuffer::typeSize() {
            return sizeof(int);
        }

        size_t IndexBuffer::count() {
            return list.size();
        }

        size_t IndexBuffer::dataSize() {
            return this->typeSize() * this->count();
        }
    }
}