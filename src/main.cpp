#include "engine/input/input.h"
#include "engine/sys.h"



struct TestApplication : public app::IApplication {

        int i = 0;

        virtual void init() {

        }

        virtual void handleEvent(SDL_Event* e) {

        }

        virtual void update(float delta) {
        }

        virtual void render() {

        }

        virtual void release() {

        }

};

int main(int argc, char** argv) {    
    TestApplication testApp;
    app::Config config;
    config.caption = "Test Application";
    config.width = 640;
    config.height = 480;
    config.app = &testApp;

    app::init(&config);
    app::update();
    app::release();

    return 0;
}