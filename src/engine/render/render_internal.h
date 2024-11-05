#ifndef RENDER_INTERNAL_H
#define RENDER_INTERNAL_H

#include "../sys.h"
#include "glw/glw.h"




namespace render {

    // Camera
    struct Camera {
        glm::mat4 proj;
        glm::mat4 view;
    };


    struct IShader {
        virtual void init() = 0;
        virtual void release() = 0;
        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void setModel(const glm::mat4& m) = 0;

        virtual void bindVertexArray() = 0;
        virtual void unbindVertexArray() = 0;
        virtual void verticesPointer() = 0;
        virtual void texCoordPointer() = 0;
    };

    struct IPostprocess : public IShader {
        virtual void setProjection(const glm::mat4& m) = 0;
        virtual void setView(const glm::mat4& m) = 0;
    };

    // Main Shader
    struct MainShader : public IShader {
        // Shaders
        glw::Shader vertex_shader;
        glw::Shader fragment_shader;
        // Program
        glw::Program program;


        virtual void init();
        virtual void release();
        virtual void bind();
        virtual void unbind();

        virtual void setModel(const glm::mat4& m);

        virtual void bindVertexArray();
        virtual void unbindVertexArray();
        virtual void verticesPointer();
        virtual void texCoordPointer();
    };

    struct Texture2DArrayShader : public IShader {
        glw::Shader vertex_shader;
        glw::Shader fragment_shader;
        glw::Program program;

        virtual void init();
        virtual void release();
        virtual void bind();
        virtual void unbind();

        virtual void setModel(const glm::mat4& m);

        virtual void bindVertexArray();
        virtual void unbindVertexArray();
        virtual void verticesPointer();
        virtual void texCoordPointer();
    };

    struct FontShader : public IShader {
        glw::Shader vertex_shader;
        glw::Shader fragment_shader;
        glw::Program program;

        virtual void init();
        virtual void release();
        virtual void bind();
        virtual void unbind();

        virtual void setModel(const glm::mat4& m);
        void setColor(glm::vec3 color);

        virtual void bindVertexArray();
        virtual void unbindVertexArray();
        virtual void verticesPointer();
        virtual void texCoordPointer();
    };

    // Postprocessing
    struct OutputPostprocessor : public IPostprocess {
        glw::Shader vertex_shader;
        glw::Shader fragment_shader;
        glw::Program program;

        // Added from IShader
        virtual void init();
        virtual void release();
        virtual void bind();
        virtual void unbind();

        virtual void setModel(const glm::mat4& m);
        void setCircle(const glm::vec2& circle);
        //void setBeat(float beat);

        void setBeat(int index, float beat);
        void setIsFX(bool fx);
        void setMaxFX(float m);
        
        virtual void bindVertexArray();
        virtual void unbindVertexArray();
        virtual void verticesPointer();
        virtual void texCoordPointer();

        // Added from IPostprocess
        virtual void setProjection(const glm::mat4& m);
        virtual void setView(const glm::mat4& m);
    };
    
    struct FontPostprocessing : public IPostprocess {
        glw::Shader vertex_shader;
        glw::Shader fragment_shader;
        glw::Program program;

        // Added from IShader
        virtual void init();
        virtual void release();
        virtual void bind();
        virtual void unbind();

        virtual void setModel(const glm::mat4& m);

        virtual void bindVertexArray();
        virtual void unbindVertexArray();
        virtual void verticesPointer();
        virtual void texCoordPointer();

        // Added from IPostprocess
        virtual void setProjection(const glm::mat4& m);
        virtual void setView(const glm::mat4& m);

        void setColor(const glm::vec3& color);
    };

    // Hidden drawing function
    void draw(IShader* shader, glw::VertexBuffer& vertices, glw::VertexBuffer& texCoords, glw::IndexBuffer& indencies);

}

#endif