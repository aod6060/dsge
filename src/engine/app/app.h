#ifndef APP_H
#define APP_H


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

    struct Config {
        std::string caption;
        uint32_t width;
        uint32_t height;
        IApplication* app;
    };

    void init(Config* config);
    void update();
    void release();

    std::string get_caption();
    uint32_t get_width();
    uint32_t get_height();

    void exit();
}

#endif