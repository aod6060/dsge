#include "engine/app/app.h"
#include "engine/input/input.h"
#include "engine/render/font/font.h"
#include "engine/render/glw/glw.h"
#include "engine/render/render.h"
#include "engine/sound/sound.h"
#include "engine/sys.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/ext/vector_common.hpp"
#include "glm/gtc/constants.hpp"
#include "glm/trigonometric.hpp"
#include <cmath>
#include <json/json.h>
#include "json/value.h"
#include <climits>
#include <sstream>
#include <vector>
#include "thirdparty/imgui/imgui.h"
#include "thirdparty/imgui/imgui_impl_sdl2.h"
#include "thirdparty/imgui/imgui_impl_opengl3.h"

struct TestApplication : public app::IApplication {
        int i = 0;

        render::glw::Texture2D icon_32;
        render::glw::Texture2DArray icon_array;

        // Custom TexCoords for texture array example
        render::glw::VertexBuffer icon_array_texCoords;

        glm::vec2 postion = glm::vec2(32.0f);

        glm::vec2 velocity = glm::vec2(0.0f);

        float speed = 64.0f;


        glm::vec2 soundPosition;

        bool isArrayTest = false;

        int32_t width;
        int32_t height;

        sound::MusicPlayer jungleMusicPlayer;
        sound::MusicPlayer happyMusicPlayer;
        sound::MusicPlayer levelMusicPlayer;
        sound::MusicPlayer menuMusicPlayer;
        sound::MusicPlayer* current = &jungleMusicPlayer;

        std::vector<sound::MusicPlayer*> musicPlayers;

        virtual void init() {

            IMGUI_CHECKVERSION();

            ImGui::CreateContext();
            
            // If I need it
            ImGuiIO& io = ImGui::GetIO();

            ImGui::StyleColorsDark();

            ImGui_ImplSDL2_InitForOpenGL(app::getWindow(), app::getContext());
            ImGui_ImplOpenGL3_Init("#version 400");


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


            render::font::loadFont("regular", "data/font/londrina_sketch_regular.ttf", 64);
            this->soundPosition = glm::vec2(render::getWidth() / 2, render::getHeight() / 2);


            sound::addMusicStream("jungle", "data/sound/music/jungle.mp3");
            sound::addMusicStream("happy", "data/sound/music/happyHeavenTrance.mp3");
            sound::addMusicStream("level", "data/sound/music/level.mp3");
            sound::addMusicStream("menu", "data/sound/music/menu.mp3");



            jungleMusicPlayer.init("jungle");
            happyMusicPlayer.init("happy");
            levelMusicPlayer.init("level");
            menuMusicPlayer.init("menu");

        }

        virtual void handleEvent(SDL_Event* e) {
            ImGui_ImplSDL2_ProcessEvent(e);
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

            glm::vec2 v = this->postion - this->soundPosition;
            float dist = glm::abs(glm::length(v));
            dist = glm::clamp(dist, 0.0f, 1024.0f);


            float actualDistance = glm::mix(0.0f, 255.0f, dist / 1024.0f);
            //float d = glm::dot(postion, soundPosition);
            glm::vec2 nv = glm::normalize(v);
            float angle = glm::degrees(atan2(-nv.x, nv.y)) + 180.0f;

            
            std::cout << "Direction: " << v.x << ", " << v.y << "\n";
            std::cout << "Distance: " << (int)(dist) << "\n";
            std::cout << "Acutal Distance: " << (int)(actualDistance) << "\n";
            std::cout << "Angle: " << (int)(angle) << "\n";
            
        }

        void renderMenu() {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();

            ImGui::NewFrame();
            ImGui::Begin("Configuration");

            ImGui::End();
            
            ImGui::EndFrame();

            ImGui::Render();

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

            /*
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
            */

            render::endFrame();

            
            std::stringstream ss;

            ss << "Position: [" << postion.x << ", " << postion.y << "]";

            render::font::getSize("regular", ss.str(), &width, &height);
            render::font::update("regular", ss.str());

            render::font_postprocess::bind();
            render::enableBlend();

            render::font_postprocess::setProjection(glm::ortho(0.0f, (float)app::get_width(), (float)app::get_height(), 0.0f));
            render::font_postprocess::setView(glm::mat4(1.0f));
            render::font_postprocess::setModel(
                glm::translate(glm::mat4(1.0f), glm::vec3(1.0, 1.0f, 0.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3((float)width, (float)height, 0.0f))
            );

            render::font_postprocess::setColor(glm::vec3(0.0f, 1.0f, 0.0f));

            render::font::bind(GL_TEXTURE0);
            render::font_postprocess::render();
            render::font::unbind(GL_TEXTURE0);

            render::disableBlend();
            render::font_postprocess::unbind();



            renderMenu();
        }

        virtual void release() {
            jungleMusicPlayer.release();
            happyMusicPlayer.release();
            levelMusicPlayer.release();
            menuMusicPlayer.release();

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