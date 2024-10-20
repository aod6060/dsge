#ifndef RENDER_INTERNAL_H
#define RENDER_INTERNAL_H

#include "../sys.h"




namespace render {

    // Main Shader
    struct MainShader {
        // Shaders
        glw::Shader vertex_shader;
        glw::Shader fragment_shader;
        // Program
        glw::Program program;


        void init();
        void release();

        void bind();
        void unbind();

        void setModel(const glm::mat4& m);

        
    };

    struct Texture2DArrayShader {

    };


}

#endif