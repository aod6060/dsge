#include "render_internal.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glw/glw.h"

namespace render {


    struct Camera {
        glm::mat4 proj;
        glm::mat4 view;
    };


    uint32_t width = 640;
    uint32_t height = 480;
    
    // Shaders
    glw::Shader vertex_shader;
    glw::Shader fragment_shader;
    // Program
    glw::Program program;
    // Default Vertex Buffer
    glw::VertexBuffer defVertices;
    // Default TexCoord Buffer
    glw::VertexBuffer defTexCoords;
    // Default Index Buffer
    glw::IndexBuffer defIndex;

    // Camera Uniform Buffer
    glw::UniformBuffer<Camera> cameraBuffer;


    void init() {
        glDisable(GL_DEPTH_TEST);

        vertex_shader.init(GL_VERTEX_SHADER, "data/shaders/main.vert.glsl");
        fragment_shader.init(GL_FRAGMENT_SHADER, "data/shaders/main.frag.glsl");

        program.init({&vertex_shader, &fragment_shader});

        program.vertexArray.createAttrib("vertices", 0);
        program.vertexArray.createAttrib("texCoords", 1);

        program.bind();
        program.uniform.createUniform("proj");
        program.uniform.createUniform("view");
        program.uniform.createUniform("model");
        program.uniform.createUniform("tex0");
        program.uniform.set1i("tex0", 0);
        
        program.vertexArray.bind();
        program.vertexArray.enable("vertices");
        program.vertexArray.enable("texCoords");
        program.vertexArray.unbind();

        program.unbind();

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

        defIndex.init();
        defIndex.add3(0, 1, 2);
        defIndex.add3(2, 1, 3);
        defIndex.update();


        // Init Camera Buffer
        cameraBuffer.init();

        cameraBuffer.value.proj = glm::ortho(0.0f, (float)getWidth(), (float)getHeight(), 0.0f);
        cameraBuffer.value.view = glm::mat4(1.0f);
        
    }

    void release() {
        cameraBuffer.release();

        defIndex.release();
        defVertices.release();

        program.release();

        fragment_shader.release();
        vertex_shader.release();
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
        program.bind();
    }

    void endShader(ShaderType type) {
        program.unbind();
    }

    void updateCameraBuffer() {
        cameraBuffer.update();
    }

    void setView(const glm::mat4& m) {
        cameraBuffer.value.view = m;
    }

    void setModel(const glm::mat4& m) {
        program.uniform.setMatrix4("model", m);
    }

    void draw() {
        program.vertexArray.bind();

        defVertices.bind();
        program.vertexArray.pointer("vertices", 3, GL_FLOAT);
        defTexCoords.bind();
        program.vertexArray.pointer("texCoords", 2, GL_FLOAT);
        defVertices.unbind();

        defIndex.bind();
        glDrawElements(GL_TRIANGLES, defIndex.count(), GL_UNSIGNED_INT, nullptr);
        defIndex.unbind();

        program.vertexArray.unbind();
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