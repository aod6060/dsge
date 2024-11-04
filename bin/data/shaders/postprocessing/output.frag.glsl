/*
    output.frag.glsl
*/
#version 400


uniform sampler2D tex0;
uniform vec2 circle;
uniform float beat; // 0.0 -> 1.0

in vec2 v_TexCoords;
out vec4 out_Color;

void main() {
    float dist = mix(0.0001, 0.01, beat);

    vec4 color = texture(tex0, v_TexCoords);


    float r = texture(tex0, vec2(v_TexCoords.x, v_TexCoords.y + -dist)).r;
    float g = texture(tex0, vec2(v_TexCoords.x + -dist, v_TexCoords.y + dist)).g;
    float b = texture(tex0, vec2(v_TexCoords.x + dist, v_TexCoords.y + dist)).b;

    color.rgb = color.rgb + mix(vec3(0.0), vec3(r, g, b), beat);
    out_Color = color;
}