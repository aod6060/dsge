#include "../../sys.h"

namespace render {
    namespace glw {
        void Texture2D::init() {
            glGenTextures(1, &this->id);
        }

        void Texture2D::release() {
            glDeleteTextures(1, &this->id);
        }

        void Texture2D::bind(GLenum active) {
            glActiveTexture(active);
            glBindTexture(GL_TEXTURE_2D, this->id);
        }

        void Texture2D::unbind(GLenum active) {
            glActiveTexture(active);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void Texture2D::texImage2D(
            int32_t level, 
            int32_t internalFormat, 
            size_t width, 
            size_t height, 
            GLenum format, 
            GLenum type, 
            const void* data) {
                this->width = width;
                this->height = height;
                glTexImage2D(
                    GL_TEXTURE_2D, 
                    level, 
                    internalFormat, 
                    width, 
                    height, 
                    0, 
                    format, 
                    type, 
                    data);    
            }

        void Texture2D::texParameter(GLenum pname, int32_t param) {
            glTexParameteri(GL_TEXTURE_2D, pname, param);
        }

        void Texture2D::createTexture2DFromFile(Texture2D* out, std::string path) {
            /*
                For now I'm going to assume every texture
                has an alpha component... So I can use

                GL_RGBA
            */
            SDL_Surface* temp = IMG_Load(path.c_str());

            if(temp == nullptr) {
                std::cout << path << " doesn't exist!";
                return;
            }


            out->init();

            out->bind(GL_TEXTURE0);

            out->texImage2D(0, GL_RGBA, temp->w, temp->h, GL_RGBA, GL_UNSIGNED_BYTE, temp->pixels);
            
            out->texParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            out->texParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            
            out->unbind(GL_TEXTURE0);

            SDL_FreeSurface(temp);
        }

    }
}