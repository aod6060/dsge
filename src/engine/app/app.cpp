#include "app_hidden.h"


namespace app {

    Config* config = nullptr;

    SDL_Window* window = nullptr;
    SDL_GLContext context = nullptr;

    bool is_running = true;

    void init(Config* _config) {
        config = _config;


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

        int32_t numberOfDisplays = SDL_GetNumVideoDisplays();

        std::cout << "This system has " << numberOfDisplays << " displays hooked up to graphics card.\n";

        for(int i = 0; i < numberOfDisplays; i++) {
            int numDisplayModes = SDL_GetNumDisplayModes(i);

            std::cout << i << " display has " << numDisplayModes << " display modes!\n";

            for(int j = 0; j < numDisplayModes; j++) {
                SDL_DisplayMode mode;

                SDL_GetDisplayMode(i, j, &mode);

                std::cout << mode.w << ", " << mode.h << " @ " << mode.refresh_rate << " : " << SDL_GetPixelFormatName(mode.format) << "\n";
            }
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


        window = SDL_CreateWindow(
            config->caption.c_str(), 
            SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, 
            config->width, 
            config->height, 
            SDL_WINDOW_OPENGL);

        context = SDL_GL_CreateContext(window);
        glewInit();

        input::init();
        render::init();
        sound::init();
        physics::init();

        if(config->app) {
            config->app->init();
        }
    }
    
    void update() {
        uint32_t pre_time = SDL_GetTicks();
        uint32_t curr_time = 0;
        float delta = 0.0f;

        SDL_Event e;

        while(is_running) {
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

                if(config->app) {
                    config->app->handleEvent(&e);
                }
            }

            if(config->app) {
                // Update Method
                config->app->update(delta);
                // Render Method
                config->app->render();
            }

            input::update(delta);

            //this->input.update(this);

            SDL_GL_SwapWindow(window);
        }
    }

    void release() {
        if(config->app) {
            config->app->release();
        }
        
        physics::release();
        sound::release();
        render::release();
        input::release();

        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);

        SDL_Quit();
    }
    
    std::string get_caption() {
        return config->caption;
    }
    
    uint32_t get_width() {
        return config->width;
    }
    
    uint32_t get_height() {
        return config->height;
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
    

}