#include "render_internal.h"

namespace render {

    void Texture2DArrayShader::init() {
        this->vertex_shader.init(GL_VERTEX_SHADER, "data/shaders/tex2darray.vert.glsl");
        this->fragment_shader.init(GL_FRAGMENT_SHADER, "data/shaders/tex2darray.frag.glsl");

        this->program.init({&this->vertex_shader, &this->fragment_shader});

        this->program.vertexArray.createAttrib("vertices", 0);
        this->program.vertexArray.createAttrib("texCoords", 1);

        this->program.bind();
        this->program.uniform.createUniform("model");
        this->program.uniform.createUniform("tex0");
        this->program.uniform.set1i("tex0", 0);

        program.uniformBlock.createUniformBlock("Camera", 0);

        program.vertexArray.bind();
        program.vertexArray.enable("vertices");
        program.vertexArray.enable("texCoords");
        program.vertexArray.unbind();

        this->program.unbind();

    }

    void Texture2DArrayShader::release() {
        this->program.release();
        this->vertex_shader.release();
        this->fragment_shader.release();
    }

    void Texture2DArrayShader::bind() {
        this->program.bind();
    }

    void Texture2DArrayShader::unbind() {
        this->program.unbind();
    }

    void Texture2DArrayShader::setModel(const glm::mat4& m) {
        this->program.uniform.setMatrix4("model", m);
    }


    void Texture2DArrayShader::bindVertexArray() {
        this->program.vertexArray.bind();
    }

    void Texture2DArrayShader::unbindVertexArray() {
        this->program.vertexArray.unbind();
    }

    void Texture2DArrayShader::verticesPointer() {
        this->program.vertexArray.pointer("vertices", 3, GL_FLOAT);
    }

    void Texture2DArrayShader::texCoordPointer() {
        this->program.vertexArray.pointer("texCoords", 3, GL_FLOAT);
    }

}