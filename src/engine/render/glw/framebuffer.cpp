#include "../../sys.h"
#include "glw.h"


namespace render {
    namespace glw {
        void Framebuffer::init() {
            glGenFramebuffers(1, &this->id);
        }

        void Framebuffer::release() {
            glDeleteFramebuffers(1, &this->id);
        }

        void Framebuffer::bind() {
            glBindFramebuffer(GL_FRAMEBUFFER, this->id);
        }

        void Framebuffer::unbind() {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void Framebuffer::attachTexture2D(GLenum attachment, Texture2D* tex, uint32_t level) {
            glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, tex->id, level);
        }

        bool Framebuffer::isComplete() {
            return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
        }
    }
}