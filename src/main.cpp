#include "engine/render/glw/glw.h"
#include "engine/sys.h"



// https://youtube.com/clip/UgkxyCtqY_D6g4ULEyuLwinqERd8N-jTzCWj?si=s1aTiUychjS-6HHu

struct TestApplication : public app::IApplication {
        int i = 0;

        render::glw::Texture2D icon_32;

        virtual void init() {
            render::glw::Texture2D::createTexture2DFromFile(&icon_32, "data/icon/icon_32.png");
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

            icon_32.bind(GL_TEXTURE0);
            render::draw();
            icon_32.unbind(GL_TEXTURE0);
            
            render::endFrame();
        }

        virtual void release() {
            icon_32.release();
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