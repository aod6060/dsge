#include "render_internal.h"

namespace render {

    namespace vertex_buffer_manager {

        static std::map<std::string, VertexBufferData> vbData;

        void add(std::string name) {
            vbData[name].buffer.init();
        }

        void release() {
            for(std::map<std::string, VertexBufferData>::iterator it = vbData.begin(); it != vbData.end(); it++ ){
                it->second.buffer.release();
            }
            vbData.clear();
        }

        void reloadInit() {

        }

        void reloadRelease() {

        }

        void add1(std::string name, float x) {
            vbData[name].buffer.add1(x);
        }

        void add2(std::string name, float x, float y) {
            vbData[name].buffer.add2(x, y);
        }

        void add3(std::string name, float x, float y, float z) {
            vbData[name].buffer.add3(x, y, z);
        }

        void add4(std::string name, float x, float y, float z, float w) {
            vbData[name].buffer.add4(x, y, z, w);
        }

        void clear(std::string name) {
            vbData[name].buffer.clear();
        }

        void bind(std::string name) {
            vbData[name].buffer.bind();
        }

        void unbind(std::string name) {
            vbData[name].buffer.unbind();
        }

        void update(std::string name) {
            vbData[name].buffer.update();
        }

        glw::VertexBuffer* getBuffer(std::string name) {
            return &vbData[name].buffer;
        }
    }
}