/*
    tex2darray.frag.glsl
*/

#version 400

uniform sampler2DArray tex0;

out vec4 out_Color;

in vec3 v_TexCoords;


void main() {
    out_Color = texture(tex0, v_TexCoords);
    //out_Color = vec4(v_TexCoords.xy, v_TexCoords.z, 1.0);

    //out_Color = texture(tex0, vec3(v_TexCoords.xy, ))
}