/*
    output.frag.glsl
*/
#version 400


uniform sampler2D tex0;

in vec2 v_TexCoords;
out vec4 out_Color;

void main() {
    //out_Color = texture(tex0, v_TexCoords);
    
    vec4 color = texture(tex0, v_TexCoords);

    //int scaled_y = int(v_TexCoords.y * 960.0);


    //color.rgb = 1.0 - color.rgb;
    //color.rgb = vec3((color.r + color.g + color.b) / 3.0);
    //color.rgb *= vec3(1.2, 1.0, 0.8);

    /*
    if((scaled_y % 2) == 0) {
        discard;
    } else {
        out_Color = color;
    }
    */
    

    out_Color = color;
}