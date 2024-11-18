#include "render_internal.h"


namespace render {

    namespace texture2D_manager {

        static std::map<std::string, Texture2DData> texture2DData;

        // This one creates an empty texture
        void add(std::string name) {
            
        }

        // Release all textures
        void release() {

        }

        // Re inits all texutre
        void reloadInit() {

        }

        // Soft releases all texture
        void reloadRelease() {

        }

        void loadFromFile(std::string name, std::string path) {

        }

        void texParameter(std::string name, GLenum pname, int32_t param) {

        }

        void bind(std::string name, GLenum tex) {

        }

        void unbind(std::string name, GLenum tex) {

        }


    }

}