#include "render.h"
#include "../sys.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glw/glw.h"

namespace render {
    uint32_t width = 640;
    uint32_t height = 480;


    // Shaders
    glw::Shader vertex_shader;
    glw::Shader fragment_shader;
    // Program
    glw::Program program;
    // Default Vertex Buffer
    glw::VertexBuffer defVertices;
    // Default Index Buffer
    glw::IndexBuffer defIndex;

    void init() {
        glDisable(GL_DEPTH_TEST);

        vertex_shader.init(GL_VERTEX_SHADER, "data/shaders/main.vert.glsl");
        fragment_shader.init(GL_FRAGMENT_SHADER, "data/shaders/main.frag.glsl");

        program.init({&vertex_shader, &fragment_shader});

        program.vertexArray.createAttrib("vertices", 0);

        program.bind();
        program.uniform.createUniform("proj");
        program.uniform.createUniform("view");
        program.uniform.createUniform("model");

        program.vertexArray.bind();
        program.vertexArray.enable("vertices");
        program.vertexArray.unbind();

        program.unbind();

        defVertices.init();
        defVertices.add3(0.0f, 0.0f, 0.0f);
        defVertices.add3(1.0f, 0.0f, 0.0f);
        defVertices.add3(0.0f, 1.0f, 0.0f);
        defVertices.add3(1.0f, 1.0f, 0.0f);
        defVertices.update();

        defIndex.init();
        defIndex.add3(0, 1, 2);
        defIndex.add3(2, 1, 3);
        defIndex.update();
    }

    void release() {
        defIndex.release();
        defVertices.release();

        program.release();

        fragment_shader.release();
        vertex_shader.release();
    }

    void clear(const glm::vec4& color) {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void startFrame() {
        program.bind();

        setProjection(glm::ortho(0.0f, (float)getWidth(), (float)getHeight(), 0.0f));
    }

    void endFrame() {
        program.unbind();
    }

    void setProjection(const glm::mat4& m) {
        program.uniform.setMatrix4("proj", m);
    }

    void setView(const glm::mat4& m) {
        program.uniform.setMatrix4("view", m);
    }

    void setModel(const glm::mat4& m) {
        program.uniform.setMatrix4("model", m);
    }

    void draw() {
        program.vertexArray.bind();
        defVertices.bind();
        program.vertexArray.pointer("vertices", 3, GL_FLOAT);
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