#ifndef IGW_H
#define IGW_H


#include <SDL.h>
#include "../../thirdparty/imgui/imgui.h"
#include "../../thirdparty/imgui/imgui_impl_sdl2.h"
#include "../../thirdparty/imgui/imgui_impl_opengl3.h"

namespace igw {

    void init();
    void handleEvent(SDL_Event* e);
    void release();

    void bind();
    void unbind();

    void reloadInit();
    void reloadRelease();
}

#endif