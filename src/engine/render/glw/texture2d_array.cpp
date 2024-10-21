#include "../../sys.h"
#include "SDL_image.h"
#include "SDL_surface.h"
#include "glw.h"


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
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, level, 0, 0, index, width, height, 1, format, type, data);
        }

        void Texture2DArray::texParameter(GLenum pname, int32_t param) {
            glTexParameteri(GL_TEXTURE_2D_ARRAY, pname, param);
        }

        void Texture2DArray::createTexture2DArrayFromFiles(Texture2DArray* out, const std::vector<std::string>& paths) {
            out->init();

            out->bind(GL_TEXTURE0);

            SDL_Surface* temp = IMG_Load(paths[0].c_str());

            size_t width = temp->w;
            size_t height = temp->h;

            if(temp == nullptr) {
                return;
            }

            out->texStorage3D(1, GL_RGBA8, temp->w, temp->h, paths.size());

            SDL_FreeSurface(temp);

            //out->texStorage3D(1, GL_RGBA8, , size_t height, size_t depth)
            for(int i = 0; i < paths.size(); i++) {
                SDL_Surface* temp2 = IMG_Load(paths[i].c_str());

                if(temp2 == nullptr) {
                    std::cout << paths[i] << " doesn't exist.";
                    // Continue for now because I'm not real sure
                    // how what to do here.

                    out->texSubImage3D(0, i, width, height, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
                    continue;
                }

                out->texSubImage3D(0, i, temp2->w, temp2->h, GL_RGBA, GL_UNSIGNED_BYTE, temp2->pixels);
                SDL_FreeSurface(temp2);
            }

            out->texParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            out->texParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            
            out->unbind(GL_TEXTURE0);
        }

    }
}