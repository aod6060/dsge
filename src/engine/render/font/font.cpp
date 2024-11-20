#include "font.h"
#include "font_hidden.h"
#include <climits>
#include <fstream>
#include <ft2build.h>
#include <vector>
#include FT_FREETYPE_H



namespace render {
    namespace font {

        FT_Library library;

        std::map<std::string, FontFace> fontFaces;

        glw::Texture2D texture;

        void init() {
            // Initialize font api...
            if(FT_Init_FreeType(&library)) {
                std::cout << "ERROR:FREETYPE: Counld not init FreeType Library\n";
                return;
            }

            texture.init();

            texture.bind(GL_TEXTURE0);
            texture.texParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            texture.texParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            texture.unbind(GL_TEXTURE0);
        }

        void release() {
            texture.release();

            std::map<std::string, FontFace>::iterator it;

            for(it = fontFaces.begin(); it != fontFaces.end(); it++) {
                it->second.release();
            }

            FT_Done_FreeType(library);
        }

        void loadFont(std::string name, std::string path, int32_t size) {
            fontFaces[name].init(library, path, size);
        }

        void update(std::string name, std::string message) {
            std::vector<uint8_t> buffer;
            std::vector<FontColor> pixels;

            int32_t width;
            int32_t height;

            fontFaces.at(name).getSize(message, &width , &height);

            fontFaces.at(name).createBuffer(message, &buffer);

            pixels.resize(width * height);

            // Create Pixels
            for(int32_t y = 0; y < height; y++) {
                for(int32_t x = 0; x < width; x++) {
                    int32_t index = y * width + x;
                    pixels[index].r = 255;
                    pixels[index].g = 255;
                    pixels[index].b = 255;
                    pixels[index].a = buffer[index];
                }
            }

            texture.bind(GL_TEXTURE0);
            texture.texImage2D(0, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
            texture.unbind(GL_TEXTURE0);
        }
        
        void bind(GLenum unit) {
            texture.bind(unit);
        }

        void unbind(GLenum unit) {
            texture.unbind(unit);
        }

        void getSize(std::string name, std::string message, int32_t* width, int32_t* height) {
            fontFaces.at(name).getSize(message, width, height);
        }

        void reloadInit() {
            texture.init();
            texture.bind(GL_TEXTURE0);
            texture.texParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            texture.texParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            texture.unbind(GL_TEXTURE0);     
        }

        void reloadRelease() {
            texture.release();
        }

        
    }
}