/*
    output.frag.glsl
*/
#version 400

#define REGULAR 0
#define INVERT 1
#define GREYSCALE 2
#define SEPIA 3
#define PIXELATE 4
#define INVERT_PIXELATE 5
#define GREYSCALE_PIXELATE 6
#define SEPIA_PIXELATE 7

uniform sampler2D tex0;

uniform int example;

// Generic Uniforms
// This is the windows resolution
uniform int screen_width;
uniform int screen_height;
// This will be (640x480 if 4:3) or (640x360 if 16:9)
uniform int render_width;
uniform int render_height;

// Pixelate Controles
uniform float pixel_size;

in vec2 v_TexCoords;
out vec4 out_Color;

vec2 pixelate_texCoords() {
    float dx = pixel_size * (1.0 / screen_width);
    float dy = pixel_size * (1.0 / screen_height);

    vec2 coord;

    coord.x = dx * floor(v_TexCoords.x / dx);
    coord.y = dy * floor(v_TexCoords.y / dy);

    return coord;
}

vec4 invert_colors(vec2 texCoords) {
    vec4 color = texture(tex0, texCoords);
    color.rgb = 1.0 - color.rgb;
    return color;
}

vec4 greyscale_colors(vec2 texCoords) {
    vec4 color = texture(tex0, texCoords);
    color.rgb = vec3((color.r + color.g + color.b) / 3.0);
    return color;  
}

vec4 sepia_colors(vec2 texCoords) {
    vec4 color = greyscale_colors(texCoords);
    color.rgb *= vec3(1.2, 1.0, 0.8);
    return color;
}

vec4 regular() {
    return texture(tex0, v_TexCoords);
}

vec4 invert() {
    return invert_colors(v_TexCoords);
}

vec4 greyscale() {
    return greyscale_colors(v_TexCoords);
}

vec4 sepia() {
    return sepia_colors(v_TexCoords);
}

vec4 pixelate() {
    return texture(tex0, pixelate_texCoords());
}

vec4 invert_pixelate() {
    return invert_colors(pixelate_texCoords());
}

vec4 greyscale_pixelate() {
    return greyscale_colors(pixelate_texCoords());
}

vec4 sepia_pixelate() {
    return sepia_colors(pixelate_texCoords());
}

void main() {

    if(example == REGULAR) {
        out_Color = regular();
    } 
    else if(example == INVERT) {
        out_Color = invert();
    } 
    else if(example == GREYSCALE) {
        out_Color = greyscale();
    } 
    else if(example == SEPIA) {
        out_Color = sepia();
    } 
    else if(example == PIXELATE) {
        out_Color = pixelate();
    } 
    else if(example == INVERT_PIXELATE) {
        out_Color = invert_pixelate();
    } 
    else if(example == GREYSCALE_PIXELATE) {
        out_Color = greyscale_pixelate();
    }
    else if(example == SEPIA_PIXELATE) {
        out_Color = sepia_pixelate();
    }
    else {
        out_Color = regular();
    }

    /*
    float size = 2.0;

    float div_size = mix(0.5, 5.0, 0.0);

    float width = 1280 / div_size;
    float height = 960 / div_size;

    float dx = size * (1.0 / width);
    float dy = size * (1.0 / height);

    vec2 coord;

    coord.x = dx * floor(v_TexCoords.x / dx);
    coord.y = dy * floor(v_TexCoords.y / dy);

    //out_Color = texture(tex0, v_TexCoords);
    
    vec4 color = texture(tex0, coord);

    int scaled_y = int(v_TexCoords.y * 960.0);


    //color.rgb = 1.0 - color.rgb;
    //color.rgb = vec3((color.r + color.g + color.b) / 3.0);
    //color.rgb *= vec3(1.2, 1.0, 0.8);

    float light = (color.r + color.g + color.b) / 3.0;

    if(light > 0.4) {
        color.rgb = vec3(1.0);
    } else {
        color.rgb = vec3(0.0);
    }
    */

    /*
    if((scaled_y % 2) == 0) {
        discard;
    } else {
        out_Color = color;
    }

    out_Color = color;
    */
}