#ifndef RENDER_INTERNAL_H
#define RENDER_INTERNAL_H

#include "../sys.h"
#include "glw/glw.h"
#include <string>



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


    namespace texture2D_manager {
        struct Texture2DData {
            render::glw::Texture2D texture;
            bool hasFile = false;
            std::string path;
            uint32_t width;
            uint32_t height;
        };
    }

    namespace texture2D_array_manager {

    }

    namespace vertex_buffer_manager {

    }

    namespace index_buffer_manager {
        
    }
}

#endif