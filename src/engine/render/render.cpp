#include "render.h"
#include "font/font.h"
#include "glm/ext/matrix_transform.hpp"
#include "render_internal.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glw/glw.h"

namespace render {
    // Shaders
    MainShader mainShader;
    Texture2DArrayShader tex2DArrayShader;
    FontShader fontShader;

    // Postprocessing
    OutputPostprocessor outputPostprocessor;
    FontPostprocessing fontPostprocessing;

    // Default Vertex Buffer
    glw::VertexBuffer defVertices;

    // Default Center Vertex Buffer
    glw::VertexBuffer defCenterVertices;

    // Default TexCoord Buffer
    glw::VertexBuffer defTexCoords;

    // Default TexCoord 3D Buffer
    glw::VertexBuffer defTexCoords3D;

    // Default Index Buffer
    glw::IndexBuffer defIndex;

    // Camera Uniform Buffer
    glw::UniformBuffer<Camera> cameraBuffer;

    ShaderType shaderType = ShaderType::ST_MAIN;

    glw::Texture2D screen;
    glw::Framebuffer screen_framebuffer;


    void init() {
        glDisable(GL_DEPTH_TEST);

        // Init Shaders
        mainShader.init();
        tex2DArrayShader.init();
        fontShader.init();

        // Init Postprocessors
        outputPostprocessor.init();
        fontPostprocessing.init();

        defVertices.init();
        defVertices.add3(0.0f, 0.0f, 0.0f);
        defVertices.add3(1.0f, 0.0f, 0.0f);
        defVertices.add3(0.0f, 1.0f, 0.0f);
        defVertices.add3(1.0f, 1.0f, 0.0f);
        defVertices.update();

        defCenterVertices.init();
        defCenterVertices.add3(-0.5f, -0.5f, 0.0f);
        defCenterVertices.add3(0.5f, -0.5f, 0.0f);
        defCenterVertices.add3(-0.5f, 0.5f, 0.0f);
        defCenterVertices.add3(0.5f, 0.5f, 0.0f);
        defCenterVertices.update();

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

        // Initialize Screen
        screen.init();
        screen.bind(GL_TEXTURE0);
        screen.texImage2D(0, GL_RGBA, getWidth(), getHeight(), GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        screen.texParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        screen.texParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        screen.texParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        screen.texParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        screen.unbind(GL_TEXTURE0);

        // Initialize Screen Framebuffer
        screen_framebuffer.init();
        screen_framebuffer.bind();
        screen_framebuffer.attachTexture2D(GL_COLOR_ATTACHMENT0, &screen, 0);
        if(!screen_framebuffer.isComplete()) {
            std::cout << "Framebuffer: wasn't created correctly!\n";
        }
        screen_framebuffer.unbind();

        font::init();
    }

    void release() {
        index_buffer_manager::release();
        vertex_buffer_manager::release();
        texture2D_array_manager::release();
        texture2D_manager::release();

        font::release();
        
        screen_framebuffer.release();

        screen.release();

        cameraBuffer.release();

        defIndex.release();

        defTexCoords3D.release();
        defTexCoords.release();
        defCenterVertices.release();
        defVertices.release();

        fontPostprocessing.release();
        outputPostprocessor.release();

        fontShader.release();
        tex2DArrayShader.release();
        mainShader.release();
    }

    void startFrame() {
        screen_framebuffer.bind();
        glViewport(0, 0, getWidth(), getHeight());

    }

    void endFrame() {
        screen_framebuffer.unbind();


        // Draw to screen...
        glViewport(0, 0, app::getWidth(), app::getHeight());
        clear(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

        outputPostprocessor.bind();

        outputPostprocessor.setProjection(glm::ortho(0.0f, (float)app::getWidth(), 0.0f, (float)app::getHeight()));
        outputPostprocessor.setView(glm::mat4(1.0f));
        outputPostprocessor.setModel(
            glm::translate(glm::mat4(1.0f), glm::vec3(0.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3((float)app::getWidth(), (float)app::getHeight(), 0.0f))
        );

        screen.bind(GL_TEXTURE0);

        outputPostprocessor.bindVertexArray();

        defVertices.bind();
        outputPostprocessor.verticesPointer();
        defTexCoords.bind();
        outputPostprocessor.texCoordPointer();
        defVertices.unbind();

        defIndex.bind();
        glDrawElements(GL_TRIANGLES, defIndex.count(), GL_UNSIGNED_INT, nullptr);
        defIndex.unbind();

        outputPostprocessor.unbindVertexArray();
        
        screen.unbind(GL_TEXTURE0);

        outputPostprocessor.unbind();
    }


    void clear(const glm::vec4& color) {
        glClearColor(color.r, color.g, color.b, color.a);
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
            case render::ShaderType::ST_FONT:
                fontShader.bind();
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
            case ShaderType::ST_FONT:
                fontShader.unbind();
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
            case ShaderType::ST_FONT:
                fontShader.setModel(m);
                break;
        }
    }

    void draw() {
        if(shaderType == ShaderType::ST_MAIN) {
            draw(&mainShader, defVertices, defTexCoords, defIndex);
        } else if(shaderType == ShaderType::ST_TEXTURE2D_ARRAY) {
            draw(&tex2DArrayShader, defVertices, defTexCoords, defIndex);
        } else if(shaderType == ShaderType::ST_FONT) {
            draw(&fontShader, defVertices, defTexCoords, defIndex);
        }
    }

    // Draw Centered
    void draw_center() {
        if(shaderType == ShaderType::ST_MAIN) {
            draw(&mainShader, defCenterVertices, defTexCoords, defIndex);
        } else if(shaderType == ShaderType::ST_TEXTURE2D_ARRAY) {
            draw(&tex2DArrayShader, defCenterVertices, defTexCoords, defIndex);
        } else if(shaderType == ShaderType::ST_FONT) {
            draw(&fontShader, defCenterVertices, defTexCoords, defIndex);
        }
    }

    void draw(glw::VertexBuffer& texCoords) {
        if(shaderType == ShaderType::ST_MAIN) {
            draw(&mainShader, defVertices, texCoords, defIndex);
        } else if(shaderType == ShaderType::ST_TEXTURE2D_ARRAY) {
            draw(&tex2DArrayShader, defVertices, texCoords, defIndex);
        } else if(shaderType == ShaderType::ST_FONT) {
            draw(&fontShader, defVertices, texCoords, defIndex);
        }
    }

    void draw_center(glw::VertexBuffer& texCoords) {
        if(shaderType == ShaderType::ST_MAIN) {
            draw(&mainShader, defCenterVertices, texCoords, defIndex);
        } else if(shaderType == ShaderType::ST_TEXTURE2D_ARRAY) {
            draw(&tex2DArrayShader, defCenterVertices, texCoords, defIndex);
        } else if(shaderType == ShaderType::ST_FONT) {
            draw(&fontShader, defCenterVertices, texCoords, defIndex);
        }    
    }

    void draw_center(std::string texCoord) {
        glw::VertexBuffer* b = vertex_buffer_manager::getBuffer(texCoord);
        draw_center(*b);
    }

    // Sending a custom vertices, texCoords, and indencies to 
    // the render
    void draw(glw::VertexBuffer& vertices, glw::VertexBuffer& texCoords, glw::IndexBuffer& indencies) {
        if(shaderType == ShaderType::ST_MAIN) {
            draw(&mainShader, vertices, texCoords, indencies);
        } else if(shaderType == ShaderType::ST_TEXTURE2D_ARRAY) {
            draw(&tex2DArrayShader, vertices, texCoords, indencies);
        } else if(shaderType == ShaderType::ST_FONT) {
            draw(&fontShader, vertices, texCoords, indencies);
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

    void enableBlend() {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void disableBlend() {
        glDisable(GL_BLEND);
    }


    /*
        The render will draw at 
        640x480 if w/h * 3 == 4 or standard screen
        640x360 if w/h * 9 == 11   wide screen
    */
    uint32_t getWidth() {
        return 640; // This will never change
    }

    uint32_t getHeight() {
        //float aspect = (float)app::get_width() / (float)app::get_height();;
        return (float)getWidth() / app::getAspect();
        //return 480;
    }

    void reloadInit() {
        glDisable(GL_DEPTH_TEST);
        std::cout << "glDisable\n";

        // Init Shaders
        mainShader.init();
        tex2DArrayShader.init();
        fontShader.init();
        std::cout << "Init Shaders\n";

        // Init Postprocessors
        outputPostprocessor.init();
        fontPostprocessing.init();
        std::cout << "Init Postprocessors\n";

        defVertices.init();
        defVertices.update();
        std::cout << "defVertices\n";

        defCenterVertices.init();
        defCenterVertices.update();
        std::cout << "defCenterVertices\n";

        defTexCoords.init();
        defTexCoords.update();
        std::cout << "defTexCoords\n";

        defTexCoords3D.init();
        defTexCoords3D.update();
        std::cout << "defTexCoords3D\n";

        defIndex.init();
        defIndex.update();
        std::cout << "defIndex\n";

        cameraBuffer.init();

        cameraBuffer.value.proj = glm::ortho(0.0f, (float)getWidth(), (float)getHeight(), 0.0f);

        cameraBuffer.update();
        cameraBuffer.bufferRange(0);
        std::cout << "cameraBuffer\n";

        std::cout << getWidth() << ", " << getHeight() << "\n";

        // Initialize Screen
        screen.init();
        screen.bind(GL_TEXTURE0);
        screen.texImage2D(0, GL_RGBA, getWidth(), getHeight(), GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        screen.texParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        screen.texParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        screen.texParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        screen.texParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        screen.unbind(GL_TEXTURE0);
        std::cout << "screen\n";

        // Initialize Screen Framebuffer
        screen_framebuffer.init();
        screen_framebuffer.bind();
        screen_framebuffer.attachTexture2D(GL_COLOR_ATTACHMENT0, &screen, 0);
        if(!screen_framebuffer.isComplete()) {
            std::cout << "Framebuffer: wasn't created correctly!\n";
        }
        screen_framebuffer.unbind();
        std::cout << "screen framebuffer\n";

        font::reloadInit();
        std::cout << "reloadInit\n";

        index_buffer_manager::reloadInit();
        std::cout << "index buffer manager\n";

        vertex_buffer_manager::reloadInit();
        std::cout << "vertex buffer manager\n";

        texture2D_array_manager::reloadInit();
        std::cout << "texture2D array manager\n";

        texture2D_manager::reloadInit();
        std::cout << "texture2D manager\n";

    }

    void reloadRelease() {
        index_buffer_manager::reloadRelease();
        vertex_buffer_manager::reloadRelease();
        texture2D_array_manager::reloadRelease();
        texture2D_manager::reloadRelease();

        font::reloadRelease();
        
        screen_framebuffer.release();

        screen.release();

        cameraBuffer.release();

        defIndex.release();

        defTexCoords3D.release();

        defTexCoords.release();

        defCenterVertices.release();

        defVertices.release();

        fontPostprocessing.release();
        outputPostprocessor.release();

        fontShader.release();
        tex2DArrayShader.release();
        mainShader.release();
    }


    namespace font_shader {
        void setColor(glm::vec3 color) {
            fontShader.setColor(color);
        }
    }

    namespace font_postprocess {
        void bind() {
            fontPostprocessing.bind();
        }

        void unbind() {
            fontPostprocessing.unbind();
        }

        void setProjection(const glm::mat4& m) {
            fontPostprocessing.setProjection(m);
        }

        void setView(const glm::mat4& m) {
            fontPostprocessing.setView(m);
        }

        void setModel(const glm::mat4& m) {
            fontPostprocessing.setModel(m);
        }

        void setColor(const glm::vec3& color) {
            fontPostprocessing.setColor(color);
        }

        void render() {
            //draw(&fontPostprocessing, defVertices, defTexCoords, defIndex);
            fontPostprocessing.bindVertexArray();

            defVertices.bind();
            fontPostprocessing.verticesPointer();
            defTexCoords.bind();
            fontPostprocessing.texCoordPointer();
            defVertices.unbind();

            defIndex.bind();
            glDrawElements(GL_TRIANGLES, defIndex.count(), GL_UNSIGNED_INT, nullptr);
            defIndex.unbind();

            fontPostprocessing.unbindVertexArray();
        }

    }

}