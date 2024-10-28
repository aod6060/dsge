#include "font_hidden.h"
#include "freetype/freetype.h"
#include <vector>


namespace render {
    namespace font {

        void FontFace::init(FT_Library library, std::string path, int32_t size) {
            this->font_face_path = path;
            this->size = size;
            this->glyph_space = this->size / 16;
            this->space = this->size / 4;
            this->tab = this->size / 2;

            this->glyph_offset = this->size;
            this->max_glyph_size = 0;

            if(FT_New_Face(library, this->font_face_path.c_str(), 0, &this->face)) {
                std::cout << "error: ttf not found\n";
            }

            FT_Set_Pixel_Sizes(this->face, 0, this->size);

            this->glyphs.resize(UCHAR_MAX);

            // Generate Glyphs
            for(uint8_t i = 0; i < this->glyphs.size(); i++) {
                if(FT_Load_Char(this->face, i, FT_LOAD_RENDER)) {
                    std::cout << "Error: Failed to load glyph\n";
                    continue;
                }

                this->glyphs[i].startX = face->glyph->bitmap_left;
                this->glyphs[i].startY = face->glyph->bitmap_top;
                this->glyphs[i].width = face->glyph->bitmap.width;
                this->glyphs[i].height = face->glyph->bitmap.rows;

                if(this->glyphs[i].height > max_glyph_size) {
                    max_glyph_size = glyphs[i].height;
                }

                if((((size - max_glyph_size) + (size - glyphs[i].startY))) < glyph_offset && (i > 32 && i < 127)) {
                    glyph_offset = ((size - max_glyph_size) + (size - glyphs[i].startY));
                }

                glyphs[i].data.resize(glyphs[i].width * glyphs[i].height);

                // Grab Data and added it to data
                for(uint32_t y = 0; y < glyphs[i].height; y++) {
                    for(uint32_t x = 0; x < glyphs[i].width; x++) {
                        uint32_t j = y * glyphs[i].width + x;
                        glyphs[i].data[j] = face->glyph->bitmap.buffer[j];
                    }
                }
            }
        }

        void FontFace::release() {

            for(int i = 0; i < glyphs.size(); i++) {
                glyphs[i].data.clear();
            }

            this->glyphs.clear();
            FT_Done_Face(this->face);
        }

        void FontFace::getSize(std::string message, int32_t* width, int32_t* height) {
            *height = this->size;

            int32_t w = 0;

            for(int i = 0; i < message.size(); i++) {
                w += glyphs[message[i]].width + glyph_space;
                
                if(message[i] == ' ') {
                    w += space;
                }

                if(message[i] == '\t') {
                    w += tab;
                }
            }

            *width = w;
        }

        void FontFace::createBuffer(std::string message, std::vector<uint8_t>* buffer) {
            int32_t width;
            int32_t height;

            this->getSize(message, &width, &height);

            // Indencies
            int32_t current = 0;
            std::vector<int32_t> indencies;
            
            for(int i = 0; i < message.size(); i++) {
                indencies.push_back(current);
                current += glyphs[message[i]].width + glyph_space;

                if(message[i] == ' ') {
                    current += space;
                }

                if(message[i] == '\t') {
                    current += tab;
                }
            }

            // Render to Buffer
            buffer->resize(width * height);
            for(int i = 0; i < message.size(); i++) {
                if(message[i] == ' ' || message[i] == '\t') {
                    continue;
                }

                int32_t startX = 0;
                int32_t startY = 0;
                int32_t gwidth = glyphs[message[i]].width;
                int32_t gheight = glyphs[message[i]].height;

                int32_t index = indencies[i];

                int32_t offset = ((size - max_glyph_size) + (size - glyphs[message[i]].startY));

                for(int32_t y = startY; y < gheight; y++) {
                    for(int32_t x = startX; x < gwidth; x++) {
                        int y_offset = y + offset;
                        y_offset -= (glyph_offset);
                        y_offset += 2;

                        int gindex = y * gwidth + x;
                        int bindex = y_offset * width + (x + index);

                        if((x + index) < 0 || x > (width - 1) || y_offset < 0 || y > (height - 1)) {
                            continue;
                        }

                        buffer->at(bindex) = glyphs[message[i]].data[gindex];
                    }
                }
            }
        }
    }
}