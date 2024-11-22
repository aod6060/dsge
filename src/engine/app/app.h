#ifndef APP_H
#define APP_H


#include "SDL_video.h"
#include <SDL.h>
#include <string>

namespace app {

    struct IApplication {
        virtual void init() = 0;
        virtual void handleEvent(SDL_Event* e) = 0;
        virtual void update(float delta) = 0;
        virtual void render() = 0;
        virtual void release() = 0;
    };

    void init(IApplication* app);
    void update();
    void release();

    //std::string get_caption();
    uint32_t getWidth();
    uint32_t getHeight();
    float getAspect();
    
    void exit();

    SDL_Window* getWindow();
    SDL_GLContext getContext();
    
    void reloadInit();
    void reloadRelease();
    
}

#endif