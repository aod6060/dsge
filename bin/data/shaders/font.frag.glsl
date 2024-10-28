/*
    font.frag.glsl
*/

#version 400

uniform sampler2D tex0;
uniform vec3 color;

out vec4 out_Color;

in vec2 v_TexCoords;

void main() {
    vec4 finalColor = texture(tex0, v_TexCoords);

    finalColor.rgb *= color;

    out_Color = finalColor;
}