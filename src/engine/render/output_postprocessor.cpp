#include "render.h"
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
        program.uniform.set1i("model", 0);
        program.uniform.createUniform("example");
        program.uniform.set1i("example", (int)test::Example::REGULAR);
        program.uniform.createUniform("screen_width");
        program.uniform.set1i("screen_width", app::get_width());
        program.uniform.createUniform("screen_height");
        program.uniform.set1i("screen_height", app::get_height());
        program.uniform.createUniform("render_width");
        program.uniform.set1i("render_width", render::getWidth());
        program.uniform.createUniform("render_height");
        program.uniform.set1i("render_height", render::getHeight());
        program.uniform.createUniform("pixel_size");
        program.uniform.set1f("pixel_size", 2.0f);
        program.uniform.createUniform("enableScanlines");
        program.uniform.set1i("enableScanlines", 0);
        program.uniform.createUniform("scanlineColor");
        program.uniform.set4f("scanlineColor", 0.0f, 0.0f, 0.0f, 1.0f);


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

    void OutputPostprocessor::setExample(test::Example example) {
        program.uniform.set1i("example", (int)example);
    }

    void OutputPostprocessor::setPixelSize(float size) {
        program.uniform.set1f("pixel_size", size);
    }

    void OutputPostprocessor::setEnableScanlines(bool b) {
        program.uniform.set1i("enableScanlines", b);
    }

    void OutputPostprocessor::setScanlineColor(const glm::vec4& color) {
        program.uniform.set4f("scanlineColor", color.x, color.y, color.z, color.w);
    }
}