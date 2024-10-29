#include "render_internal.h"

namespace render {


    // Added from IShader
    void FontPostprocessing::init() {
        this->vertex_shader.init(GL_VERTEX_SHADER, "data/shaders/postprocessing/font.vert.glsl");
        this->fragment_shader.init(GL_FRAGMENT_SHADER, "data/shaders/postprocessing/font.frag.glsl");

        this->program.init({&this->vertex_shader, &this->fragment_shader});

        this->program.vertexArray.createAttrib("vertices", 0);
        this->program.vertexArray.createAttrib("texCoords", 1);

        this->bind();
        // Uniforms
        program.uniform.createUniform("proj");
        program.uniform.createUniform("view");
        program.uniform.createUniform("model");
        program.uniform.createUniform("tex0");
        program.uniform.set1i("tex0", 0);
        program.uniform.createUniform("color");
        program.uniform.set3i("color", 1.0f, 1.0f, 1.0f);

        // Attributes
        bindVertexArray();
        program.vertexArray.enable("vertices");
        program.vertexArray.enable("texCoords");
        unbindVertexArray();

        this->unbind();
    }

    void FontPostprocessing::release() {
        this->program.release();
        this->vertex_shader.release();
        this->fragment_shader.release();
    }

    void FontPostprocessing::bind() {
        program.bind();
    }

    void FontPostprocessing::unbind() {
        program.unbind();
    }


    void FontPostprocessing::setModel(const glm::mat4& m) {
        program.uniform.setMatrix4("model", m);
    }


    void FontPostprocessing::bindVertexArray() {
        program.vertexArray.bind();
    }

    void FontPostprocessing::unbindVertexArray() {
        program.vertexArray.unbind();
    }

    void FontPostprocessing::verticesPointer() {
        program.vertexArray.pointer("vertices", 3, GL_FLOAT);
    }

    void FontPostprocessing::texCoordPointer() {
        program.vertexArray.pointer("texCoords", 2, GL_FLOAT);
    }

    // Added from IPostprocess
    void FontPostprocessing::setProjection(const glm::mat4& m) {
        program.uniform.setMatrix4("proj", m);
    }

    void FontPostprocessing::setView(const glm::mat4& m) {
        program.uniform.setMatrix4("view", m);
    }

    void FontPostprocessing::setColor(const glm::vec3& color) {
        program.uniform.set3f("color", color.r, color.g, color.b);
    }

}