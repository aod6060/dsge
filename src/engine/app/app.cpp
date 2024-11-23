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
            SDL_WINDOWPOS_CENTERED_DISPLAY(config::getConfig()->application.display), 
            SDL_WINDOWPOS_CENTERED_DISPLAY(config::getConfig()->application.display), 
            displayMode.w, 
            displayMode.h, 
            flags);

        SDL_SetWindowDisplayMode(window, &displayMode);

        
        //SDL_SetWindowBrightness(window, 0.0f);

        context = SDL_GL_CreateContext(window);
        glewInit();

        input::init();
        render::init();
        igw::init();
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

                igw::handleEvent(&e);

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

            SDL_GL_SwapWindow(window);
        }
    }

    void release() {
        if(app) {
            app->release();
        }
        
        physics::release();
        sound::release();
        igw::release();
        render::release();
        input::release();

        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);

        SDL_Quit();
    }
    
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
            SDL_WINDOWPOS_CENTERED_DISPLAY(config::getConfig()->application.display), 
            SDL_WINDOWPOS_CENTERED_DISPLAY(config::getConfig()->application.display), 
            displayMode.w, 
            displayMode.h, 
            flags);

        
        SDL_SetWindowDisplayMode(window, &displayMode);

        context = SDL_GL_CreateContext(window);
        glewInit();

        render::reloadInit();
        igw::reloadInit();
    }

    void reloadRelease() {
        igw::reloadRelease();
        render::reloadRelease();

        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
    }

    
}