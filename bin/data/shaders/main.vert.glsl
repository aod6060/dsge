/*
    main.vert.glsl
*/
#version 400

layout(location=0) in vec3 vertices;


uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main() {
    gl_Position = proj * view * model * vec4(vertices, 1.0);
}