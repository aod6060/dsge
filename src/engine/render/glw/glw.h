#ifndef GLW_H
#define GLW_H

#define GLEW_NO_GLU
#include <GL/glew.h>
#include <string>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace render {
    namespace glw {
        // Shader
        struct Shader {
            uint32_t id = 0;

            void init(GLenum type, std::string path);
            void release();
        };

        // Vertex Array
        struct VertexArray {
            uint32_t id = 0;

            std::map<std::string, uint32_t> attribs;

            void init();
            void release();

            void bind();
            void unbind();

            void createAttrib(std::string name, uint32_t id);

            void enable(std::string name);
            void disable(std::string name);
            void pointer(std::string name, GLint size, GLenum type);

        };

        // Uniform
        struct Program;

        struct Uniform {
            Program* program;

            std::map<std::string, uint32_t> uniforms;

            void createUniform(std::string name);

            void init(Program* program);
            void release();

            // Integers
            void set1i(std::string name, int x);
            void set2i(std::string name, int x, int y);
            void set3i(std::string name, int x, int y, int z);
            void set4i(std::string name, int x, int y, int z, int w);

            // Floats
            void set1f(std::string name, float x);
            void set2f(std::string name, float x, float y);
            void set3f(std::string name, float x, float y, float z);
            void set4f(std::string name, float x, float y, float z, float w);

            // Matrix
            void setMatrix2(std::string name, const glm::mat2& m);
            void setMatrix3(std::string name, const glm::mat3& m);
            void setMatrix4(std::string name, const glm::mat4& m);

        };

        // Uniform Block
        struct UniformBlock {
            Program* program;

            std::map<std::string, uint32_t> uniformBlocks;

            void init(Program* program);
            void release();

            void createUniformBlock(std::string name, uint32_t index);
        };

        // Program
        struct Program {
            uint32_t id = 0;
            std::vector<Shader*> shaders;
            VertexArray vertexArray;
            Uniform uniform;
            UniformBlock uniformBlock;
            
            void init(const std::vector<Shader*>& shaders);
            void release();

            void bind();
            void unbind();
        };

        // VertexBuffer
        struct VertexBuffer {
            std::vector<float> list;
            uint32_t id = 0;

            void add1(float x);
            void add2(float x, float y);
            void add3(float x, float y, float z);
            void add4(float x, float y, float z, float w);
            void clear();

            void init();
            void release();

            void update();

            void bind();
            void unbind();

            size_t typeSize();
            size_t count();
            size_t dataSize();
        };

        // IndexBuffer
        struct IndexBuffer {
            std::vector<int> list;
            uint32_t id = 0;

            void add1(int x);
            void add2(int x, int y);
            void add3(int x, int y, int z);
            void add4(int x, int y, int z, int w);
            void clear();

            void init();
            void release();

            void update();

            void bind();
            void unbind();
            
            size_t typeSize();
            size_t count();
            size_t dataSize();
        };

        // Texture2D
        struct Texture2D {
            uint32_t id = 0;
            uint32_t width = 0;
            uint32_t height = 0;

            void init();
            void release();

            void bind(GLenum active);
            void unbind(GLenum active);

            void texImage2D(
                int32_t level, 
                int32_t internalFormat, 
                size_t width, 
                size_t height, 
                GLenum format, 
                GLenum type, 
                const void* data);

            void texParameter(GLenum pname, int32_t param);

            static void createTexture2DFromFile(Texture2D* out, std::string path);


        };

        // Texture2DArray
        struct Texture2DArray {
            uint32_t id = 0;
            uint32_t width = 0;
            uint32_t height = 0;

            void init();
            void release();

            void bind(GLenum active);
            void unbind(GLenum active);

            void texStorage3D(size_t levels, GLenum internalFormat, size_t width, size_t height, size_t depth);

            void texSubImage3D(int32_t level, int32_t index, size_t width, size_t height, GLenum format, GLenum type, const void* data);

            void texParameter(GLenum pname, int32_t param);

            static void createTexture2DArrayFromFiles(Texture2DArray* out, const std::vector<std::string>& paths);
        };

        // UniformBuffer
        // Reference: https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL
        template<typename T> 
        struct UniformBuffer {
            T value;
            uint32_t id;

            void init() {
                glGenBuffers(1, &this->id);
            }

            void release() {
                glDeleteBuffers(1, &this->id);
            }

            void bind() {
                glBindBuffer(GL_UNIFORM_BUFFER, this->id);
            }

            void unbind() {
                glBindBuffer(GL_UNIFORM_BUFFER, 0);
            }

            void update() {
                this->bind();
                glBufferData(GL_UNIFORM_BUFFER, typeSize(), &value, GL_DYNAMIC_DRAW);
                this->unbind();
            }

            size_t typeSize() {
                return sizeof(T);
            }

            void bufferRange(uint32_t index) {
                glBindBufferBase(GL_UNIFORM_BUFFER, index, this->id);
            }
        };

        // Framebuffer
        struct Framebuffer {
            uint32_t id = 0;

            void init();
            void release();

            void bind();
            void unbind();

            void attachTexture2D(GLenum attachment, Texture2D* tex, uint32_t level);

            bool isComplete();

        };
    }
}
#endif