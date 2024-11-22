#include "app.h"
#include "SDL_video.h"
#include "app_hidden.h"


namespace app {

    //Config* config = nullptr;
    IApplication* app = nullptr;

    SDL_DisplayMode displayMode;

    SDL_Window* window = nullptr;
    SDL_GLContext context = nullptr;

    bool is_running = true;

    void init(IApplication* _app) {
        app = _app;

        /*
            Load print logo
        */
        std::ifstream in("data/startup/logo.txt");

        std::string line;
        while(std::getline(in, line)) {
            std::cout << line << "\n";
        }

        in.close();

        std::cout << VERSION_FULL_NAME << "\n\n";


        SDL_Init(SDL_INIT_EVERYTHING);
        /*
        int32_t numberOfDisplays = SDL_GetNumVideoDisplays();

        std::cout << "This system has " << numberOfDisplays << " displays hooked up to graphics card.\n";

        for(int i = 0; i < numberOfDisplays; i++) {
            int numDisplayModes = SDL_GetNumDisplayModes(i);

            std::cout << i << " display has " << numDisplayModes << " display modes!\n";

            for(int j = 0; j < numDisplayModes; j++) {
                SDL_DisplayMode mode;

                SDL_GetDisplayMode(i, j, &mode);

                std::cout << "[" << j <<"]" << mode.w << ", " << mode.h << " @ " << mode.refresh_rate << " : " << SDL_GetPixelFormatName(mode.format) << "\n";
            }
        }
        */

        config::init();

        uint32_t flags = SDL_WINDOW_OPENGL;

        if(config::getConfig()->application.fullscreen) {
            flags |= SDL_WINDOW_FULLSCREEN;
        }

        SDL_GetDisplayMode(config::getConfig()->application.display, config::getConfig()->application.resolution, &displayMode);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        window = SDL_CreateWindow(
            config::getConfig()->application.caption.c_str(), 
            SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, 
            displayMode.w, 
            displayMode.h, 
            flags);

        SDL_SetWindowDisplayMode(window, &displayMode);

        context = SDL_GL_CreateContext(window);
        glewInit();

        input::init();
        render::init();
        sound::init();
        physics::init();

        if(app) {
            app->init();
        }
    }
    
    void update() {
        uint32_t pre_time = SDL_GetTicks();
        uint32_t curr_time = 0;
        float delta = 0.0f;

        SDL_Event e;

        while(is_running) {
            // Sound Volume
            sound::setMasterVolume(config::getConfig()->sound.masterVolume);
            sound::setMusicVolume(config::getConfig()->sound.musicVolume);
            sound::setSoundFXVolume(config::getConfig()->sound.soundFXVolume);
            
            // Calculate Delta
            curr_time = SDL_GetTicks();
            delta = (curr_time - pre_time) / 1000.0f;
            pre_time = curr_time;

            // Handle Event
            while(SDL_PollEvent(&e)) {
                if(e.type == SDL_QUIT) {
                    app::exit();
                }

                //this->input.handleEvent(this);
                input::handleEvent(&e);

                if(app) {
                    app->handleEvent(&e);
                }
            }

            if(app) {
                // Update Method
                app->update(delta);
                // Render Method
                app->render();
            }

            input::update(delta);

            //this->input.update(this);

            SDL_GL_SwapWindow(window);
        }
    }

    void release() {
        if(app) {
            app->release();
        }
        
        physics::release();
        sound::release();
        render::release();
        input::release();

        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);

        SDL_Quit();
    }
    
    /*
    std::string get_caption() {
        return config->caption;
    }
    */

    uint32_t getWidth() {
        return displayMode.w;
    }
    
    uint32_t getHeight() {
        return displayMode.h;
    }

    float getAspect() {
        return (float)getWidth() / (float)getHeight();
    }

    void exit() {
        is_running = false;
    }

    SDL_Window* getWindow() {
        return window;
    }
    
    SDL_GLContext getContext() {
        return context;
    }
    
    void reloadInit() {
        uint32_t flags = SDL_WINDOW_OPENGL;

        if(config::getConfig()->application.fullscreen) {
            flags |= SDL_WINDOW_FULLSCREEN;
        }

        SDL_GetDisplayMode(config::getConfig()->application.display, config::getConfig()->application.resolution, &displayMode);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        window = SDL_CreateWindow(
            config::getConfig()->application.caption.c_str(), 
            SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, 
            displayMode.w, 
            displayMode.h, 
            flags);

        SDL_SetWindowDisplayMode(window, &displayMode);

        context = SDL_GL_CreateContext(window);
        glewInit();

        render::reloadInit();
    }

    void reloadRelease() {
        render::reloadRelease();

        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
    }

    
}