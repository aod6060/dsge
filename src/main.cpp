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
            render::clear(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
            render::startFrame();

            render::setView(glm::mat4(1.0f));
            render::setModel(
                glm::translate(glm::mat4(1.0f), glm::vec3(32.0f, 32.0f, 0.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(32.0f, 32.0f, 0.0f))
            );

            render::draw();
            
            render::endFrame();
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