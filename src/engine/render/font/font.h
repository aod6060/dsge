#ifndef FONT_H
#define FONT_H


#define GLEW_NO_GLU
#include <GL/glew.h>
#include <string>

namespace render {
    namespace font {

        void init();
        void release();
        
        void loadFont(std::string name, std::string path, int32_t size);

        void update(std::string name, std::string message);

        void bind(GLenum unit);
        void unbind(GLenum unit);

        void getSize(std::string name, std::string message, int32_t* width, int32_t* height);

        void reloadInit();
        void reloadRelease();
        
    }
}

#endif