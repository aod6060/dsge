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
    void endShader();

    // Note this shouldn't be part of the public api.
    //void setProjection(const glm::mat4& m);

    void updateCameraBuffer();
    void setView(const glm::mat4& m);

    // This has to be inside the startShader and
    // endShader functions
    void setModel(const glm::mat4& m);

    void draw();

    // Sending a custom texCoord buffer to the render
    void draw(glw::VertexBuffer& texCoords);

    // Sending a custom vertices, texCoords, and indencies to 
    // the render
    void draw(glw::VertexBuffer& vertices, glw::VertexBuffer& texCoords, glw::IndexBuffer& indencies);
    /*
        The render will draw at 
        640x480 if w/h * 3 == 4 or standard screen (4:3)
        640x360 if w/h * 9 == 11   wide screen     (16:9)
    */
    uint32_t getWidth();
    uint32_t getHeight();

    namespace test {
        // This section contains stuff to test the OutputPostprocess

        enum Example {
            REGULAR = 0,
            INVERT,
            GREYSCALE,
            SEPIA,
            PIXELATE,
            INVERT_PIXELATE,
            GREYSCALE_PIXELATE,
            SEPIA_PIXELATE
        };

        void setExample(Example example);
        Example getExample();

        void setTextureLinear(bool isLinear);

        // Pixelate
        void setPixelSize(float size);
    }
}

#endif