#include "glw/glw.h"
#include "render_internal.h"


namespace render {

    namespace texture2D_manager {

        static std::map<std::string, Texture2DData> texture2DData;

        // This one creates an empty texture
        void add(std::string name) {
            texture2DData[name].texture.init();
        }

        // Release all textures
        void release() {
            for(std::map<std::string, Texture2DData>::iterator it = texture2DData.begin(); it != texture2DData.end(); it++) {
                it->second.texture.release();
            }
            texture2DData.clear();
        }

        // Re inits all texutre
        void reloadInit() {
            for(std::map<std::string, Texture2DData>::iterator it = texture2DData.begin(); it != texture2DData.end(); it++) {

                if(it->second.hasFile) {
                    glw::Texture2D::createTexture2DFromFile(&it->second.texture, it->second.path);
                } else {
                    it->second.texture.init();

                    it->second.texture.bind(GL_TEXTURE0);

                    it->second.texture.texImage2D(
                        0, 
                        GL_RGBA, 
                        it->second.width, 
                        it->second.height, 
                        GL_RGBA,
                        GL_UNSIGNED_BYTE, 
                        nullptr);

                    it->second.texture.texParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                    it->second.texture.texParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    it->second.texture.unbind(GL_TEXTURE0);
                }
            }
        }

        // Soft releases all texture
        void reloadRelease() {
            for(std::map<std::string, Texture2DData>::iterator it = texture2DData.begin(); it != texture2DData.end(); it++) {
                it->second.texture.release();
            }
        }

        void loadFromFile(std::string name, std::string path) {
            glw::Texture2D::createTexture2DFromFile(&texture2DData[name].texture, path);
            texture2DData[name].hasFile = true;
            texture2DData[name].path = path;
        }

        void texParameter(std::string name, GLenum pname, int32_t param) {
            texture2DData[name].texture.texParameter(pname, param);
        }

        void texImage2D(
            std::string name,
            int32_t level,
            int32_t internalFormat,
            size_t width,
            size_t height,
            GLenum format,
            GLenum type,
            const void* data
        ) {
            texture2DData[name].width = width;
            texture2DData[name].height = height;
            texture2DData[name].texture.texImage2D(
                level, 
                internalFormat, 
                width, 
                height, 
                format, 
                type, 
                data
            );
        }

        void bind(std::string name, GLenum tex) {
            texture2DData[name].texture.bind(tex);
        }

        void unbind(std::string name, GLenum tex) {
            texture2DData[name].texture.unbind(tex);
        }


    }

}