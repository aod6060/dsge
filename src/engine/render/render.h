#ifndef RENDER_H
#define RENDER_H


#include "glw/glw.h"
#include "font/font.h"
#include <vector>

namespace render {

    enum ShaderType {
        ST_MAIN = 0,
        ST_TEXTURE2D_ARRAY,
        ST_FONT
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

    // Draw Centered
    void draw_center();
    
    // Sending a custom texCoord buffer to the render
    void draw(glw::VertexBuffer& texCoords);

    void draw_center(glw::VertexBuffer& texCoords);
    
    // Sending a custom vertices, texCoords, and indencies to 
    // the render
    void draw(glw::VertexBuffer& vertices, glw::VertexBuffer& texCoords, glw::IndexBuffer& indencies);


    void enableBlend();
    void disableBlend();

    /*
        The render will draw at 
        640x480 if w/h * 3 == 4 or standard screen (4:3)
        640x360 if w/h * 9 == 11   wide screen     (16:9)
    */
    uint32_t getWidth();
    uint32_t getHeight();

    namespace font_shader {
        void setColor(glm::vec3 color);
    }

    namespace font_postprocess {
        void bind();
        void unbind();
        void setProjection(const glm::mat4& m);
        void setView(const glm::mat4& m);
        void setModel(const glm::mat4& m);
        void setColor(const glm::vec3& color);
        void render();
    }


    namespace texture2D_manager {
        // This one creates an empty texture
        void add(std::string name);
        // Release all textures
        void release();
        // Re inits all texutre
        void reloadInit();
        // Soft releases all texture
        void reloadRelease();

        void loadFromFile(std::string name, std::string path);

        void texParameter(std::string name, GLenum pname, int32_t param);
        
        void texImage2D(
            std::string name,
            int32_t level,
            int32_t internalFormat,
            size_t width,
            size_t height,
            GLenum format,
            GLenum type,
            const void* data
        );

        void bind(std::string name, GLenum tex);
        void unbind(std::string name, GLenum tex);
    }

    namespace texture2D_array_manager {
        void add(std::string name);

        void release();

        void reloadInit();

        void reloadRelease();

        void loadFromFile(std::string name, std::vector<std::string> paths);

        void texStorage3D(std::string name, size_t levels, GLenum internalFormat, size_t width, size_t height, size_t depth);

        void texSubImage3D(std::string name, int32_t level, int32_t index, size_t width, size_t height, GLenum format, GLenum type, const void* data);

        void texParameter(std::string name, GLenum pname, int32_t param);

        void bind(std::string name, GLenum tex);

        void unbind(std::string name, GLenum tex);
    }

    namespace vertex_buffer_manager {

    }

    namespace index_buffer_manager {

    }
}

#endif