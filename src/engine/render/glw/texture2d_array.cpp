#include "../../sys.h"


namespace render {
    namespace glw {

        void Texture2DArray::init() {
            glGenTextures(1, &this->id);
        }

        void Texture2DArray::release() {
            glDeleteTextures(1, &this->id);
        }

        void Texture2DArray::bind(GLenum active) {
            glActiveTexture(active);
            glBindTexture(GL_TEXTURE_2D_ARRAY, this->id);
        }

        void Texture2DArray::unbind(GLenum active) {
            glActiveTexture(active);
            glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
        }

        void Texture2DArray::texStorage3D(size_t levels, GLenum internalFormat, size_t width, size_t height, size_t depth) {
            glTexStorage3D(GL_TEXTURE_2D_ARRAY, levels, internalFormat, width, height, depth);
        }

        void Texture2DArray::texSubImage3D(int32_t level, int32_t index, size_t width, size_t height, GLenum format, GLenum type, const void* data) {
            
        }

        void Texture2DArray::texParameter(GLenum pname, int32_t param) {

        }

        void Texture2DArray::createTexture2DArrayFromFiles(Texture2DArray* out, const std::vector<std::string>& paths) {

        }

    }
}