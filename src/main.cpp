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

        sound::MusicPlayer musicPlayer;
        sound::SoundFXPlayer soundFXPlayer;

        struct PositioningTest {
            glm::vec2 direction;
            float distance;
            float actualDistance;
            float angle;
            float maxDistance = 1024.0f;
        } positioningTest;

        struct VolumeControls {
            float masterVolume = 1.0f;
            float musicVolume = 1.0f;
            float soundFXVolume = 1.0f;
        } volumeControls;

        std::vector<std::string> musicNamesMenuItems;
        std::string currentName = "jungle";

        std::vector<std::string> soundFXNamesMenuItems;
        std::string currentSFXName = "explosion";

        float musicPosition = 0.0f;

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

            sound::getMusicStreamNames(musicNamesMenuItems);

            sound::addSoundFXStream("explosion", "data/sound/sfx/explosion.wav");
            sound::addSoundFXStream("jump", "data/sound/sfx/jump.wav");
            sound::addSoundFXStream("lazer", "data/sound/sfx/lazer.wav");
            sound::addSoundFXStream("pickup", "data/sound/sfx/pickup.wav");
            sound::addSoundFXStream("powerup", "data/sound/sfx/powerup.wav");
            sound::addSoundFXStream("random", "data/sound/sfx/random.wav");
            sound::addSoundFXStream("select", "data/sound/sfx/select.wav");

            sound::getSoundFXStreamNames(this->soundFXNamesMenuItems);


            musicPlayer.init(this->currentName);
            //musicPlayer.play(-1);


            soundFXPlayer.init(this->currentSFXName);
            soundFXPlayer.setScaledDistance(1024);
            soundFXPlayer.setPosition(this->soundPosition);

            //soundFXPlayer.play(-1, 0);
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

            positioningTest.direction = this->postion - this->soundPosition;
            positioningTest.distance = glm::abs(glm::length(positioningTest.direction));
            positioningTest.distance = glm::clamp(positioningTest.distance, 0.0f, positioningTest.maxDistance);


            positioningTest.actualDistance = glm::mix(0.0f, 255.0f,  positioningTest.distance / positioningTest.maxDistance);
            //float d = glm::dot(postion, soundPosition);
            glm::vec2 nv = glm::normalize(positioningTest.direction);
            positioningTest.angle = glm::degrees(atan2(-nv.x, nv.y)) + 180.0f;  


            sound::setMasterVolume(volumeControls.masterVolume);
            sound::setMusicVolume(volumeControls.musicVolume);
            sound::setSoundFXVolume(volumeControls.soundFXVolume);


            sound::setListenerPosition(this->postion);
            
            if(soundFXPlayer.isPlaying()) {
                soundFXPlayer.setPosition(this->soundPosition);
                soundFXPlayer.update();
            }
        }

        void renderMenu() {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();

            ImGui::NewFrame();
            ImGui::Begin("Configuration");

            ImGui::Text("Sound Controls");
            ImGui::SliderFloat("Master Volume", &volumeControls.masterVolume, 0.0f, 1.0f);
            ImGui::SliderFloat("Music Volume", &volumeControls.musicVolume, 0.0f, 1.0f);
            ImGui::SliderFloat("Sound FX Volume", &volumeControls.soundFXVolume, 0.0f, 1.0f);
            ImGui::Separator();

            ImGui::Text("Position Test");

            ImGui::Text("Direction: [%f, %f]", this->positioningTest.direction.x, this->positioningTest.direction.y);
            ImGui::Text("Distance: %f", this->positioningTest.distance);
            ImGui::Text("Actual Distance: %f", this->positioningTest.actualDistance);
            ImGui::Text("Angle: %f", this->positioningTest.angle);
            ImGui::Separator();
            

            ImGui::PushID("music_test");

            ImGui::Text("Music Test");
            // Yes this works :)
            if(ImGui::BeginCombo("Music Player Names", currentName.data())) {
                for(int i = 0; i < musicNamesMenuItems.size(); i++) {
                    bool is_selected = (currentName == musicNamesMenuItems[i]);

                    if(ImGui::Selectable(musicNamesMenuItems[i].data(), is_selected)) {
                        currentName = musicNamesMenuItems[i];
                        musicPlayer.stop();
                        //musicPlayer.name = currentName;
                        musicPlayer.setName(currentName);
                        //musicPlayer.play(-1);
                    }

                    if(is_selected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }

                ImGui::EndCombo();
            }

            if(musicPlayer.isPlaying()) {
                if(ImGui::Button("Stop")) {
                    musicPlayer.stop();
                }

                if(ImGui::Button("Rewind")) {
                    musicPlayer.rewind();
                }

                if(musicPlayer.isPaused()) {
                    if(ImGui::Button("Resume")) {
                        musicPlayer.resume();
                    }
                } else {
                    if(ImGui::Button("Pause")) {
                        musicPlayer.pause();
                    }
                }

                this->musicPosition = musicPlayer.getPosition();

                ImGui::Text("%s/%s", musicPlayer.toCurrentPositionString().c_str(), musicPlayer.toMaxTimeString().c_str());
                ImGui::SameLine();
                if(ImGui::SliderFloat("Music Position", &this->musicPosition, 0.0f, musicPlayer.getMusicDuration(), "")) {
                    // Do something
                    musicPlayer.setPosition(this->musicPosition);
                }
            } else {
                if(ImGui::Button("Play")) {
                    musicPlayer.play(-1);
                }
            }

            ImGui::PopID();

            ImGui::Separator();

            ImGui::PushID("sound_fx_test");

            ImGui::Text("Sound FX Test");
            if(ImGui::BeginCombo("Sound FX Names", this->currentSFXName.data())) {
                for(int i = 0; i < this->soundFXNamesMenuItems.size(); i++) {
                    bool is_selected = (this->currentSFXName == this->soundFXNamesMenuItems[i]);

                    if(ImGui::Selectable(soundFXNamesMenuItems[i].data(), is_selected)) {
                        currentSFXName = soundFXNamesMenuItems[i];
                        soundFXPlayer.stop();
                        //musicPlayer.name = currentName;
                        soundFXPlayer.setName(currentSFXName);
                        //musicPlayer.play(-1);
                    }

                    if(is_selected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }

            if(!soundFXPlayer.isPlaying()) {
                if(ImGui::Button("Play")) {
                    soundFXPlayer.play(-1, 0);
                }
            }

            ImGui::PopID();

            ImGui::Text("Sound FX 2D Test");

            ImGui::PushID("sound_fx_2d_test");

            if(!soundFXPlayer.isPlaying()) {
                if(ImGui::Button("Play")) {
                    soundFXPlayer.play(-1, 0, true);
                }
            }

            ImGui::PopID();
            
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
            soundFXPlayer.stop();
            soundFXPlayer.release();

            musicPlayer.stop();
            musicPlayer.release();

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