#include "render_internal.h"


namespace render {
    void FontShader::init() {
        this->vertex_shader.init(GL_VERTEX_SHADER, "data/shaders/font.vert.glsl");
        this->fragment_shader.init(GL_FRAGMENT_SHADER, "data/shaders/font.frag.glsl");

        this->program.init({&this->vertex_shader, &this->fragment_shader});

        this->program.vertexArray.createAttrib("vertices", 0);
        this->program.vertexArray.createAttrib("texCoords", 1);

        program.bind();
        // Uniforms
        program.uniform.createUniform("model");
        program.uniform.createUniform("tex0");
        program.uniform.set1i("tex0", 0);
        program.uniform.createUniform("color");
        program.uniform.set3f("color", 1.0f, 1.0f, 1.0f);
        // UniformBlocks
        program.uniformBlock.createUniformBlock("Camera", 0);
        // Attributes
        program.vertexArray.bind();
        program.vertexArray.enable("vertices");
        program.vertexArray.enable("texCoords");
        program.vertexArray.unbind();

        program.unbind();
    }

    void FontShader::release() {
        this->program.release();
        this->vertex_shader.release();
        this->fragment_shader.release();
    }

    void FontShader::bind() {
        this->program.bind();
    }

    void FontShader::unbind() {
        this->program.unbind();
    }

    void FontShader::setModel(const glm::mat4& m) {
        this->program.uniform.setMatrix4("model", m);
    }

    void FontShader::setColor(glm::vec3 color) {
        this->program.uniform.set3f("color", color.r, color.g, color.b);
    }
    
    void FontShader::bindVertexArray() {
        this->program.vertexArray.bind();
    }

    void FontShader::unbindVertexArray() {
        this->program.vertexArray.unbind();
    }

    void FontShader::verticesPointer() {
        this->program.vertexArray.pointer("vertices", 3, GL_FLOAT);
    }

    void FontShader::texCoordPointer() {
        this->program.vertexArray.pointer("texCoords", 2, GL_FLOAT);
    }

}