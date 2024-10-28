/*
    font.vert.glsl
*/
#version 400

layout(location=0) in vec3 vertices;
layout(location=1) in vec2 texCoords;

layout(std140) uniform Camera {
    mat4 proj;
    mat4 view;
};

uniform mat4 model;

out vec2 v_TexCoords;

void main() {
    gl_Position = proj * view * model * vec4(vertices, 1.0);
    v_TexCoords = texCoords;
}