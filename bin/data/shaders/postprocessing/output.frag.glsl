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

uniform bool enableScanlines;
uniform vec4 scanlineColor;

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

    vec4 color = vec4(0.0, 0.0, 0.0, 1.0);
    if(example == REGULAR) {
        color = regular();
    } 
    else if(example == INVERT) {
        color = invert();
    } 
    else if(example == GREYSCALE) {
        color = greyscale();
    } 
    else if(example == SEPIA) {
        color = sepia();
    } 
    else if(example == PIXELATE) {
        color = pixelate();
    } 
    else if(example == INVERT_PIXELATE) {
        color = invert_pixelate();
    } 
    else if(example == GREYSCALE_PIXELATE) {
        color = greyscale_pixelate();
    }
    else if(example == SEPIA_PIXELATE) {
        color = sepia_pixelate();
    }
    else {
        color = regular();
    }

    if(enableScanlines) {
        int scaled_y = int(v_TexCoords.y * screen_height);

        if((scaled_y % 2) == 0) {
            out_Color = scanlineColor;
        } else {
            out_Color = color;
        }
    } else {
        out_Color = color;
    }
}