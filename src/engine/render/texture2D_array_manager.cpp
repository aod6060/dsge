#include "glw/glw.h"
#include "render_internal.h"


namespace render {

    namespace texture2D_array_manager {

        static std::map<std::string, Texture2DArrayData> tex2DArrayData;

        void add(std::string name) {
            tex2DArrayData[name].texture.init();
        }

        void release() {
            for(std::map<std::string, Texture2DArrayData>::iterator it = tex2DArrayData.begin(); it != tex2DArrayData.end(); it++) {
                it->second.texture.release();
            }
            tex2DArrayData.clear();
        }

        void reloadInit() {
            for(std::map<std::string, Texture2DArrayData>::iterator it = tex2DArrayData.begin(); it != tex2DArrayData.end(); it++) {
                if(it->second.hasFiles) {
                    glw::Texture2DArray::createTexture2DArrayFromFiles(&it->second.texture, it->second.paths);
                } else {
                    /*
                    it->second.texture.init();

                    it->second.texture.bind(GL_TEXTURE0);

                    it->second.texture
                    it->second.texture.unbind(GL_TEXTURE0);
                    */
                    // Not real sure what to put here for so I'll just init
                    it->second.texture.init();
                }
            }
        }

        void reloadRelease() {
            for(std::map<std::string, Texture2DArrayData>::iterator it = tex2DArrayData.begin(); it != tex2DArrayData.end(); it++) {
                it->second.texture.release();
            }
        }

        void loadFromFile(std::string name, std::vector<std::string> paths) {
            tex2DArrayData[name].hasFiles = true;
            for(int i = 0; i < paths.size(); i++) {
                tex2DArrayData[name].paths.push_back(paths[i]);
            }
            glw::Texture2DArray::createTexture2DArrayFromFiles(&tex2DArrayData[name].texture, paths);
        }

        void texStorage3D(std::string name, size_t levels, GLenum internalFormat, size_t width, size_t height, size_t depth) {
            tex2DArrayData[name].texture.texStorage3D(levels, internalFormat, width, height, depth);
        }

        void texSubImage3D(std::string name, int32_t level, int32_t index, size_t width, size_t height, GLenum format, GLenum type, const void* data) {
            tex2DArrayData[name].texture.texSubImage3D(level, index, width, height, format, type, data);
        }

        void texParameter(std::string name, GLenum pname, int32_t param) {
            tex2DArrayData[name].texture.texParameter(pname, param);
        }

        void bind(std::string name, GLenum tex) {
            tex2DArrayData[name].texture.bind(tex);
        }

        void unbind(std::string name, GLenum tex) {
            tex2DArrayData[name].texture.unbind(tex);
        }
    
    }
}