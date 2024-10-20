#include "render_internal.h"


namespace render {


    void MainShader::init() {
        this->vertex_shader.init(GL_VERTEX_SHADER, "data/shaders/main.vert.glsl");
        this->fragment_shader.init(GL_FRAGMENT_SHADER, "data/shaders/main.frag.glsl");

        this->program.init({&this->vertex_shader, &this->fragment_shader});

        this->program.vertexArray.createAttrib("vertices", 0);
        this->program.vertexArray.createAttrib("texCoords", 1);

        program.bind();
        // Uniforms
        program.uniform.createUniform("model");
        program.uniform.createUniform("tex0");
        program.uniform.set1i("tex0", 0);
        // UniformBlocks
        program.uniformBlock.createUniformBlock("Camera", 0);
        // Attributes
        program.vertexArray.bind();
        program.vertexArray.enable("vertices");
        program.vertexArray.enable("texCoords");
        program.vertexArray.unbind();

        program.unbind();
    }

    void MainShader::release() {
        this->program.release();

    }

    void MainShader::bind() {
        this->program.bind();
    }

    void MainShader::unbind() {
        this->program.unbind();
    }

    void MainShader::setModel(const glm::mat4& m) {
        this->program.uniform.setMatrix4("model", m);
    }

    void MainShader::bindVertexArray() {
        this->program.vertexArray.bind();
    }

    void MainShader::unbindVertexArray() {
        this->program.vertexArray.unbind();
    }

    
    void MainShader::verticesPointer() {
        this->program.vertexArray.pointer("vertices", 3, GL_FLOAT);
    }

    void MainShader::texCoordPointer() {
        this->program.vertexArray.pointer("texCoords", 2, GL_FLOAT);
    }

}