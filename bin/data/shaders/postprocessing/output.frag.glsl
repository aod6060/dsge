/*
    output.frag.glsl
*/
#version 400


uniform sampler2D tex0;
uniform float beat[8]; // 0.0 -> 1.0
uniform vec2 circle;
uniform bool isFX;
uniform float maxFX;

in vec2 v_TexCoords;
out vec4 out_Color;




vec4 handleFX() {
    vec4 color = texture(tex0, v_TexCoords);

    //float dist = mix(0.0001, 0.01, beat);

    float dist[8];

    for(int i = 0; i < 8; i++) {
        dist[i] = mix(0.0f, maxFX, beat[i]);
    }



    // Red
    //vec3 r = vec3(texture(tex0, vec2(v_TexCoords.x, v_TexCoords.y)).r, 0.0, 0.0);
    float r = texture(tex0, vec2(v_TexCoords.x, v_TexCoords.y-dist[0])).r;
    
    // Green
    float g = texture(tex0, vec2(v_TexCoords.x+dist[1], v_TexCoords.y-dist[1])).g;

    // Blue
    float b = texture(tex0, vec2(v_TexCoords.x+dist[2], v_TexCoords.y)).b;

    // Yellow
    vec2 y = texture(tex0, vec2(v_TexCoords.x+dist[3], v_TexCoords.y+dist[3])).rg;

    // Magenta
    vec2 m = texture(tex0, vec2(v_TexCoords.x, v_TexCoords.y+dist[4])).rb;

    // Cyan
    vec2 c = texture(tex0, vec2(v_TexCoords.x-dist[5], v_TexCoords.y+dist[5])).gb;
    
    // Orange
    vec2 o = texture(tex0, vec2(v_TexCoords.x-dist[6], v_TexCoords.y)).rg;
    o.y *= 0.5;

    // Purple
    vec2 p = texture(tex0, vec2(v_TexCoords.x-dist[7], v_TexCoords.y-dist[7])).rb;
    p.x *= 0.5;

    vec3 finalColor = 
        vec3(r, 0.0, 0.0) +
        vec3(0.0, g, 0.0) +
        vec3(0.0, 0.0, b) +
        vec3(y.x, y.y, 0.0) +
        vec3(m.x, 0.0, m.y) +
        vec3(0.0, c.x, c.y) +
        vec3(o.x, o.y, 0.0) +
        vec3(p.x, 0.0, p.y);

    
    return vec4(color.rgb + finalColor, color.a);
}

void main() {

    if(isFX) {
        out_Color = handleFX();
    } else {
        out_Color = texture(tex0, v_TexCoords);
    }
    /*
    float dist = mix(0.0001, 0.01, beat);
    vec4 color = texture(tex0, v_TexCoords);
    //float r = texture(tex0, vec2(v_TexCoords.x, v_TexCoords.y + -dist)).r;
    //float g = texture(tex0, vec2(v_TexCoords.x + -dist, v_TexCoords.y + dist)).g;
    //float b = texture(tex0, vec2(v_TexCoords.x + dist, v_TexCoords.y + dist)).b;

    //float r = 
    color.rgb = color.rgb + mix(vec3(0.0), vec3(r, g, b), beat);
    out_Color = color;
    */
}