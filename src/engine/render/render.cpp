#include "render.h"
#include "render_internal.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glw/glw.h"

namespace render {

    uint32_t width = 640;
    uint32_t height = 480;

    MainShader mainShader;
    Texture2DArrayShader tex2DArrayShader;

    // Default Vertex Buffer
    glw::VertexBuffer defVertices;
    // Default TexCoord Buffer
    glw::VertexBuffer defTexCoords;
    // Default TexCoord 3D Buffer
    glw::VertexBuffer defTexCoords3D;

    // Default Index Buffer
    glw::IndexBuffer defIndex;

    // Camera Uniform Buffer
    glw::UniformBuffer<Camera> cameraBuffer;


    ShaderType shaderType = ShaderType::ST_MAIN;

    void init() {
        glDisable(GL_DEPTH_TEST);

        mainShader.init();
        tex2DArrayShader.init();

        defVertices.init();
        defVertices.add3(0.0f, 0.0f, 0.0f);
        defVertices.add3(1.0f, 0.0f, 0.0f);
        defVertices.add3(0.0f, 1.0f, 0.0f);
        defVertices.add3(1.0f, 1.0f, 0.0f);
        defVertices.update();

        defTexCoords.init();
        defTexCoords.add2(0.0f, 0.0f);
        defTexCoords.add2(1.0f, 0.0f);
        defTexCoords.add2(0.0f, 1.0f);
        defTexCoords.add2(1.0f, 1.0f);
        defTexCoords.update();

        defTexCoords3D.init();
        defTexCoords3D.add3(0.0f, 0.0f, 0.0f);
        defTexCoords3D.add3(1.0f, 0.0f, 0.0f);
        defTexCoords3D.add3(0.0f, 1.0f, 0.0f);
        defTexCoords3D.add3(1.0f, 1.0f, 0.0f);
        defTexCoords3D.update();

        defIndex.init();
        defIndex.add3(0, 1, 2);
        defIndex.add3(2, 1, 3);
        defIndex.update();


        // Init Camera Buffer
        cameraBuffer.init();

        cameraBuffer.value.proj = glm::ortho(0.0f, (float)getWidth(), (float)getHeight(), 0.0f);
        cameraBuffer.value.view = glm::mat4(1.0f);
        
        cameraBuffer.update();
        cameraBuffer.bufferRange(0);
    }

    void release() {
        cameraBuffer.release();

        defIndex.release();

        defTexCoords3D.release();
        defTexCoords.release();
        defVertices.release();

        tex2DArrayShader.release();
        mainShader.release();
    }

    void startFrame() {
        // TODO: Add in framebuffer so I can scale to different screen sizes
    }

    void endFrame() {
        // TODO: Add in framebuffer so I can scale to different screen sizes
    }


    void clear(const glm::vec4& color) {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void startShader(ShaderType type) {
        shaderType = type;
        //mainShader.bind();

        switch(shaderType) {
            case ShaderType::ST_MAIN:
                mainShader.bind();
                break;
            case ShaderType::ST_TEXTURE2D_ARRAY:
                tex2DArrayShader.bind();
                break;
        }
    }

    void endShader() {
        switch(shaderType) {
            case ShaderType::ST_MAIN:
                mainShader.unbind();
                break;
            case ShaderType::ST_TEXTURE2D_ARRAY:
                tex2DArrayShader.unbind();
                break;
        }
    }

    void updateCameraBuffer() {
        cameraBuffer.update();
    }

    void setView(const glm::mat4& m) {
        cameraBuffer.value.view = m;
    }

    void setModel(const glm::mat4& m) {
        //program.uniform.setMatrix4("model", m);
        //mainShader.setModel(m);
        switch(shaderType) {
            case ShaderType::ST_MAIN:
                mainShader.setModel(m);
                break;
            case ShaderType::ST_TEXTURE2D_ARRAY:
                tex2DArrayShader.setModel(m);
                break;
        }
    }

    void draw() {
        if(shaderType == ShaderType::ST_MAIN) {
            draw(&mainShader, defVertices, defTexCoords, defIndex);
        } else if(shaderType == ShaderType::ST_TEXTURE2D_ARRAY) {
            draw(&tex2DArrayShader, defVertices, defTexCoords, defIndex);
        }
    }


    void draw(glw::VertexBuffer& texCoords) {
        if(shaderType == ShaderType::ST_MAIN) {
            draw(&mainShader, defVertices, texCoords, defIndex);
        } else if(shaderType == ShaderType::ST_TEXTURE2D_ARRAY) {
            draw(&tex2DArrayShader, defVertices, texCoords, defIndex);
        }
    }

    // Sending a custom vertices, texCoords, and indencies to 
    // the render
    void draw(glw::VertexBuffer& vertices, glw::VertexBuffer& texCoords, glw::IndexBuffer& indencies) {
        if(shaderType == ShaderType::ST_MAIN) {
            draw(&mainShader, vertices, texCoords, indencies);
        } else if(shaderType == ShaderType::ST_TEXTURE2D_ARRAY) {
            draw(&tex2DArrayShader, vertices, texCoords, indencies);
        }
    }

    // This is a hidden function to simplify the problem.
    void draw(IShader* shader, glw::VertexBuffer& vertices, glw::VertexBuffer& texCoords, glw::IndexBuffer& indencies) {
        shader->bindVertexArray();
        vertices.bind();
        shader->verticesPointer();
        texCoords.bind();
        shader->texCoordPointer();
        vertices.unbind();
        indencies.bind();
        glDrawElements(GL_TRIANGLES, indencies.count(), GL_UNSIGNED_INT, nullptr);
        indencies.unbind();
        shader->unbindVertexArray();
    }

    /*
        The render will draw at 
        640x480 if w/h * 3 == 4 or standard screen
        640x360 if w/h * 9 == 11   wide screen
    */
    uint32_t getWidth() {
        return width;
    }

    uint32_t getHeight() {
        return height;
    }


}