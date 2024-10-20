#ifndef RENDER_H
#define RENDER_H


#include "glw/glw.h"

namespace render {

    enum ShaderType {
        ST_MAIN = 0,
        ST_TEXTURE2D_ARRAY
    };

    void init();
    void release();

    void startFrame();
    void endFrame();

    void clear(const glm::vec4& color);
    
    void startShader(ShaderType type);
    void endShader(ShaderType type);

    // Note this shouldn't be part of the public api.
    //void setProjection(const glm::mat4& m);

    void updateCameraBuffer();
    void setView(const glm::mat4& m);

    // This has to be 
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