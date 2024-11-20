#include "render_internal.h"

namespace render {
    namespace index_buffer_manager {
        static std::map<std::string, IndexBufferData> ibData;

        void add(std::string name) {
            ibData[name].buffer.init();
        }

        void release() {
            for(std::map<std::string, IndexBufferData>::iterator it = ibData.begin(); it != ibData.end(); it++ ){
                it->second.buffer.release();
            }
            ibData.clear();
        }

        void reloadInit() {
            for(std::map<std::string, IndexBufferData>::iterator it = ibData.begin(); it != ibData.end(); it++ ){
                it->second.buffer.init();
                it->second.buffer.update();
            }
        }

        void reloadRelease() {
            for(std::map<std::string, IndexBufferData>::iterator it = ibData.begin(); it != ibData.end(); it++ ){
                it->second.buffer.release();
            }
        }

        void add1(std::string name, float x) {
            ibData[name].buffer.add1(x);
        }

        void add2(std::string name, float x, float y) {
            ibData[name].buffer.add2(x, y);
        }

        void add3(std::string name, float x, float y, float z) {
            ibData[name].buffer.add3(x, y, z);
        }

        void add4(std::string name, float x, float y, float z, float w) {
            ibData[name].buffer.add4(x, y, z, w);
        }

        void clear(std::string name) {
            ibData[name].buffer.clear();
        }

        void bind(std::string name) {
            ibData[name].buffer.bind();
        }

        void unbind(std::string name) {
            ibData[name].buffer.unbind();
        }

        void update(std::string name) {
            ibData[name].buffer.update();
        }

        glw::IndexBuffer* getBuffer(std::string name) {
            return &ibData[name].buffer;
        }   
    }
}