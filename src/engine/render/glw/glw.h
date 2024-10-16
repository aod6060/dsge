#ifndef GLW_H
#define GLW_H

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

        // Program
        struct Program {
            uint32_t id = 0;
            std::vector<Shader*> shaders;
            VertexArray vertexArray;
            Uniform uniform;

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

    }
}
#endif