#ifndef RENDER_H
#define RENDER_H


#include "glw/glw.h"

namespace render {
    void init();
    void release();

    void clear(const glm::vec4& color);
    void startFrame();
    void endFrame();

    // Note this shouldn't be part of the public api.
    void setProjection(const glm::mat4& m);
    void setView(const glm::mat4& m);
    void setModel(const glm::mat4& m);

    void draw();

    /*
        The render will draw at 
        640x480 if w/h * 3 == 4 or standard screen (4:3)
        640x360 if w/h * 9 == 11   wide screen     (16:9)
    */
    uint32_t getWidth();
    uint32_t getHeight();
}

#endif