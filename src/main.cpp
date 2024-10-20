#include "engine/input/input.h"
#include "engine/render/glw/glw.h"
#include "engine/render/render.h"
#include "engine/sys.h"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/gtc/constants.hpp"



// https://youtube.com/clip/UgkxyCtqY_D6g4ULEyuLwinqERd8N-jTzCWj?si=s1aTiUychjS-6HHu

struct TestApplication : public app::IApplication {
        int i = 0;

        render::glw::Texture2D icon_32;

        glm::vec2 postion = glm::vec2(32.0f);

        glm::vec2 velocity = glm::vec2(0.0f);

        float speed = 64.0f;

        virtual void init() {
            render::glw::Texture2D::createTexture2DFromFile(&icon_32, "data/icon/icon_32.png");
        }

        virtual void handleEvent(SDL_Event* e) {
            
        }

        virtual void update(float delta) {
            // Horizontal
            if(input::isKeyPressed(input::Keyboard::KEYS_LEFT)) {
                this->velocity.x = -1;
            } else if(input::isKeyPressed(input::Keyboard::KEYS_RIGHT)) {
                this->velocity.x = 1;
            } else {
                this->velocity.x = 0;
            }

            // Vertical
            if(input::isKeyPressed(input::Keyboard::KEYS_UP)) {
                this->velocity.y = -1;
            } else if(input::isKeyPressed(input::Keyboard::KEYS_DOWN)) {
                this->velocity.y = 1;
            } else {
                this->velocity.y = 0;
            }

            // Normalize Velocity so it goes the same speed in the diaganal
            if(this->velocity != glm::zero<glm::vec2>()) {
                this->velocity = glm::normalize(this->velocity);
            }

            // Add it to the postion
            this->postion += velocity * speed * delta;

        }

        virtual void render() {
            render::startFrame();

            render::clear(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

            render::setView(glm::mat4(1.0f));
            render::updateCameraBuffer();

            render::startShader(render::ShaderType::ST_MAIN);

            //render::setView(glm::mat4(1.0f));
            render::setModel(
                glm::translate(glm::mat4(1.0f), glm::vec3(this->postion, 0.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(32.0f, 32.0f, 0.0f))
            );

            icon_32.bind(GL_TEXTURE0);
            render::draw();
            icon_32.unbind(GL_TEXTURE0);
            
            render::endShader(render::ShaderType::ST_MAIN);

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