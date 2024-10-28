#include "engine/input/input.h"
#include "engine/render/font/font.h"
#include "engine/render/glw/glw.h"
#include "engine/render/render.h"
#include "engine/sys.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/gtc/constants.hpp"
#include <json/json.h>
#include "json/value.h"
#include <climits>
#include <sstream>

// https://youtube.com/clip/UgkxyCtqY_D6g4ULEyuLwinqERd8N-jTzCWj?si=s1aTiUychjS-6HHu
struct TestApplication : public app::IApplication {
        int i = 0;

        render::glw::Texture2D icon_32;
        render::glw::Texture2DArray icon_array;

        // Custom TexCoords for texture array example
        render::glw::VertexBuffer icon_array_texCoords;

        glm::vec2 postion = glm::vec2(32.0f);

        glm::vec2 velocity = glm::vec2(0.0f);

        float speed = 64.0f;

        bool isArrayTest = false;

        int32_t width;
        int32_t height;

        virtual void init() {
            render::glw::Texture2D::createTexture2DFromFile(&icon_32, "data/icon/icon_32.png");

            render::glw::Texture2DArray::createTexture2DArrayFromFiles(&icon_array, {
                "data/icon/icon_32.png",
                "data/icon/icon_32_green.png",
                "data/icon/icon_32_blue.png",
                "data/icon/icon_32_magenta.png"
            });

            icon_array_texCoords.init();
            icon_array_texCoords.add3(0.0f, 0.0f, 0.0f);
            icon_array_texCoords.add3(1.0f, 0.0f, 1.0f);
            icon_array_texCoords.add3(0.0f, 1.0f, 2.0f);
            icon_array_texCoords.add3(1.0f, 1.0f, 3.0f);
            icon_array_texCoords.update();


            render::font::loadFont("regular", "data/font/londrina_sketch_regular.ttf", 32);

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


            if(input::isKeyPressedOnce(input::Keyboard::KEYS_TAB)) {
                isArrayTest = !isArrayTest;
            }
        }

        virtual void render() {
            render::startFrame();

            render::clear(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

            render::setView(glm::mat4(1.0f));
            render::updateCameraBuffer();


            if(isArrayTest) {
                render::startShader(render::ShaderType::ST_TEXTURE2D_ARRAY);

                //render::setView(glm::mat4(1.0f));
                render::setModel(
                    glm::translate(glm::mat4(1.0f), glm::vec3(this->postion, 0.0f)) *
                    glm::scale(glm::mat4(1.0f), glm::vec3(32.0f, 32.0f, 0.0f))
                );

                icon_array.bind(GL_TEXTURE0);
                render::draw(icon_array_texCoords);
                icon_array.unbind(GL_TEXTURE0);

                render::endShader();

            } else {
                render::startShader(render::ShaderType::ST_MAIN);

                //render::setView(glm::mat4(1.0f));
                render::setModel(
                    glm::translate(glm::mat4(1.0f), glm::vec3(this->postion, 0.0f)) *
                    glm::scale(glm::mat4(1.0f), glm::vec3(32.0f, 32.0f, 0.0f))
                );

                icon_32.bind(GL_TEXTURE0);
                render::draw();
                icon_32.unbind(GL_TEXTURE0);

                render::endShader();
            }


            std::stringstream ss;

            ss << "Position: [" << postion.x << ", " << postion.y << "]";

            render::font::getSize("regular", ss.str(), &width, &height);
            render::font::update("regular", ss.str());

            render::startShader(render::ShaderType::ST_FONT);
            render::enableBlend();

            render::setModel(
                glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0f, 0.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3((float)width, (float)height, 0.0f))
            );

            render::font_shader::setColor(glm::vec3(1.0f, 0.0f, 0.0f));
            
            render::font::bind(GL_TEXTURE0);
            render::draw();
            render::font::unbind(GL_TEXTURE0);

            render::disableBlend();
            render::endShader();

            render::endFrame();
        }

        virtual void release() {
            icon_array_texCoords.release();
            icon_array.release();
            icon_32.release();
        }

};


void load_config(app::Config* config) {
    std::ifstream in("config.json");
    Json::Value root;
    in >> root;
    in.close();

    
    // App
    Json::Value app = root["app"];

    config->caption = app["caption"].asString();
    config->width = app["width"].asUInt();
    config->height = app["height"].asUInt();
}

int main(int argc, char** argv) { 
    TestApplication testApp;
    app::Config config;
    //config.caption = "Test Application";
    //config.width = 640 * 2; // 1280
    //config.height = 480 * 2; // 960

    load_config(&config);
    
    config.app = &testApp;

    app::init(&config);
    app::update();
    app::release();

    return 0;
}