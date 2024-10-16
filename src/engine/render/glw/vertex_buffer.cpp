#include "../../sys.h"


namespace render {
    namespace glw {

        void VertexBuffer::add1(float x) {
            this->list.push_back(x);
        }

        void VertexBuffer::add2(float x, float y) {
            this->list.push_back(x);
            this->list.push_back(y);
        }

        void VertexBuffer::add3(float x, float y, float z) {
            this->list.push_back(x);
            this->list.push_back(y);
            this->list.push_back(z);
        }

        void VertexBuffer::add4(float x, float y, float z, float w) {
            this->list.push_back(x);
            this->list.push_back(y);
            this->list.push_back(z);
            this->list.push_back(w);
        }

        void VertexBuffer::clear() {
            this->list.clear();
        }

        void VertexBuffer::init() {
            glGenBuffers(1, &this->id);
        }

        void VertexBuffer::release() {
            glDeleteBuffers(1, &this->id);
        }

        void VertexBuffer::update() {
            this->bind();
            glBufferData(GL_ARRAY_BUFFER, this->dataSize(), this->list.data(), GL_DYNAMIC_DRAW);
            this->unbind();
        }

        void VertexBuffer::bind() {
            glBindBuffer(GL_ARRAY_BUFFER, this->id);
        }

        void VertexBuffer::unbind() {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        size_t VertexBuffer::typeSize() {
            return sizeof(float);
        }

        size_t VertexBuffer::count() {
            return list.size();
        }

        size_t VertexBuffer::dataSize() {
            return this->typeSize() * this->count();
        }

    }
}