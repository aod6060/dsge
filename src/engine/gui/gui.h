#ifndef GUI_H
#define GUI_H

#include <string>
#include <vector>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "../lw/lw.h"

namespace gui {


    struct LWStateGui : public lua_wrapper::LWState {};


    enum GuiComponentType {
        GCT_LABEL = 0,
        GCT_BUTTON,
        GCT_MAX_SIZE
    };

    struct Component {
        GuiComponentType type;
        glm::vec2 position;
        std::string text;

    };

    struct Container {
        std::string path = "";

        LWStateGui state;


        void setFilePath(std::string path);

        void init();

        void release();
    };


}


#endif