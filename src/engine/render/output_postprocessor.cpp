#include "render_internal.h"


namespace render {
    // Added from IShader
    void OutputPostprocessor::init() {
        this->vertex_shader.init(GL_VERTEX_SHADER, "data/shaders/postprocessing/output.vert.glsl");
        this->fragment_shader.init(GL_FRAGMENT_SHADER, "data/shaders/postprocessing/output.frag.glsl");

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
        program.uniform.createUniform("circle");
        program.uniform.createUniform("beat");

        // Attributes
        bindVertexArray();
        program.vertexArray.enable("vertices");
        program.vertexArray.enable("texCoords");
        unbindVertexArray();

        this->unbind();
    }

    void OutputPostprocessor::release() {
        this->program.release();
        this->vertex_shader.release();
        this->fragment_shader.release();
    }

    void OutputPostprocessor::bind() {
        program.bind();
    }

    void OutputPostprocessor::unbind() {
        program.unbind();
    }

    void OutputPostprocessor::setModel(const glm::mat4& m) {
        program.uniform.setMatrix4("model", m);
    }

    void OutputPostprocessor::bindVertexArray() {
        program.vertexArray.bind();
    }

    void OutputPostprocessor::unbindVertexArray() {
        program.vertexArray.unbind();
    }

    void OutputPostprocessor::verticesPointer() {
        program.vertexArray.pointer("vertices", 3, GL_FLOAT);
    }

    void OutputPostprocessor::texCoordPointer() {
        program.vertexArray.pointer("texCoords", 2, GL_FLOAT);
    }

    // Added from IPostprocess
    void OutputPostprocessor::setProjection(const glm::mat4& m) {
        program.uniform.setMatrix4("proj", m);
    }

    void OutputPostprocessor::setView(const glm::mat4& m) {
        program.uniform.setMatrix4("view", m);
    }

    void OutputPostprocessor::setCircle(const glm::vec2& circle) {
        program.uniform.set2f("circle", circle.x, circle.y);
    }

    void OutputPostprocessor::setBeat(float beat) {
        program.uniform.set1f("beat", beat);
    }
}