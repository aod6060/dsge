/*
    main.vert.glsl
*/
#version 400

uniform sampler2D tex0;

out vec4 out_Color;

in vec2 v_TexCoords;

void main() {
    //out_Color = vec4(v_TexCoords, 0.0, 1.0);
    out_Color = texture(tex0, v_TexCoords);
}