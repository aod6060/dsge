#include "SDL_mixer.h"
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
#include <random>
#include <sstream>
#include <vector>
#include "thirdparty/imgui/imgui.h"
#include "thirdparty/imgui/imgui_impl_sdl2.h"
#include "thirdparty/imgui/imgui_impl_opengl3.h"
#include <chrono>

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


        bool isAutoPlay = false;
        bool isMusicLooping = true;
        int32_t musicAmountOfRepeats = 1; // 1 -> 255

        bool isSoundFXAutoPlay = false;
        bool isSoundFXAutoPlay2D = false;
        bool isSoundFXLooping = false;
        int32_t soundFXAmountOfRepeats = 1; // 1 -> 255
        
        // Player Section
        bool isPlayerWarp = false;

        std::mt19937 mrand;

        glm::vec3 fontColor = glm::vec3(1.0f);

        static void sound_visual_fx(void* userdata, uint8_t* stream, int len) {
            //std::cout << len << "\n";
            TestApplication* app = (TestApplication*)userdata;

            for(int i = 0; i < len; i++) {
                //stream[i] = (uint8_t)(app->mrand() % 255);
                //stream[i] = (uint8_t)(glm::sin(glm::radians((float)(i % 360))) * 255);
                //stream[i] = (uint8_t)(2.0f * glm::atan((glm::radians((float)(i % 360)) / 2.0f)) * 255) * 0.1f;


            }
        }

        virtual void init() {

            mrand = std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count());

            IMGUI_CHECKVERSION();

            ImGui::CreateContext();
            
            // If I need it
            ImGuiIO& io = ImGui::GetIO();

            ImGui::StyleColorsClassic();
            ImGui::GetStyle().GrabRounding = 4.0f;
            ImGui::GetStyle().WindowRounding = 4.0f;
            ImGui::GetStyle().FrameRounding = 2.0f;

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

            Mix_SetPostMix(TestApplication::sound_visual_fx, this);
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


            positioningTest.direction = this->postion - this->soundPosition;
            positioningTest.distance = glm::abs(glm::length(positioningTest.direction));
            positioningTest.distance = glm::clamp(positioningTest.distance, 0.0f, soundFXPlayer.scaledDistance);


            positioningTest.actualDistance = glm::mix(0.0f, 255.0f,  positioningTest.distance / soundFXPlayer.scaledDistance);
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

            if(this->isPlayerWarp) {
                if(input::isMouseButtonPressedOnce(input::MouseButtons::MBS_LEFT) && !input::isKeyPressed(input::Keyboard::KEYS_LCTRL)) {
                    //this->postion = input::getPosition();

                    glm::vec2 pos = input::getPosition();

                    glm::vec2 screenSize = glm::vec2((float)app::get_width(), (float)app::get_height());

                    glm::vec2 unit_pos = pos / screenSize;

                    glm::vec2 render_pos = unit_pos * glm::vec2(render::getWidth(), render::getHeight());


                    std::cout << "Position: " << pos.x << ", " << pos.y << "\n";
                    std::cout << "ScreenSize: " << screenSize.x << ", " << screenSize.y << "\n";
                    std::cout << "UnitPos: " << unit_pos.x << ", " << unit_pos.y << "\n";
                    std::cout << "RenderPos: " << render_pos.x << ", " << render_pos.y << "\n";

                    this->postion = render_pos;
                }
            }
        }

        void playMusic() {
            if(this->isMusicLooping) {
                musicPlayer.play(-1);
            } else {
                musicPlayer.play(this->musicAmountOfRepeats);
            }
        }

        void playSoundFX() {
            if(this->isSoundFXAutoPlay2D) {
                if(isSoundFXLooping) {
                    soundFXPlayer.play(-1, -1, true);
                } else {
                    soundFXPlayer.play(-1, this->soundFXAmountOfRepeats - 1, true);
                }
            } else {
                if(isSoundFXLooping) {
                    soundFXPlayer.play(-1, -1);
                } else {
                    soundFXPlayer.play(-1, this->soundFXAmountOfRepeats - 1);
                }
            }
        }

        void sound_configuration() {
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

                            if(this->isAutoPlay) {
                                this->playMusic();
                            }
                        }

                        if(is_selected) {
                            ImGui::SetItemDefaultFocus();
                        }
                    }

                    ImGui::EndCombo();
                }

                ImGui::Checkbox("Is Auto Play", &this->isAutoPlay);
                ImGui::SameLine();
                ImGui::Checkbox("Is Looping", &this->isMusicLooping);

                if(!this->isMusicLooping) {
                    ImGui::SliderInt("Amount of Repeats", &this->musicAmountOfRepeats, 1, 255);
                    ImGui::InputInt("Amount of Repeats: Input", &this->musicAmountOfRepeats);

                    if(this->musicAmountOfRepeats < 1) {
                        this->musicAmountOfRepeats = 1;
                    }
                    if(this->musicAmountOfRepeats > 255) {
                        this->musicAmountOfRepeats = 255;
                    }
                }

                if(musicPlayer.isPlaying()) {
                    if(ImGui::Button("Stop")) {
                        musicPlayer.stop();
                    }
                    ImGui::SameLine();
                    if(ImGui::Button("Rewind")) {
                        musicPlayer.rewind();
                    }
                    ImGui::SameLine();
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

                    float grab_temp = ImGui::GetStyle().GrabRounding;
                    ImVec4 slider_grab = ImGui::GetStyle().Colors[ImGuiCol_SliderGrab];
                    ImVec4 slider_grab_active = ImGui::GetStyle().Colors[ImGuiCol_SliderGrabActive];

                    ImGui::GetStyle().GrabRounding = 0.0f;
                    ImGui::GetStyle().Colors[ImGuiCol_SliderGrab]            = ImVec4(1.0f, 0.5f, 0.5f, 1.0f);
                    ImGui::GetStyle().Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.5f, 0.5f, 1.0f, 1.0f);

                    ImGui::Text("%s/%s", musicPlayer.toCurrentPositionString().c_str(), musicPlayer.toMaxTimeString().c_str());
                    ImGui::SameLine();
                    if(ImGui::SliderFloat("Music Position", &this->musicPosition, 0.0f, musicPlayer.getMusicDuration(), "")) {
                        // Do something
                        musicPlayer.setPosition(this->musicPosition);
                    }

                    ImGui::GetStyle().GrabRounding = grab_temp;
                    ImGui::GetStyle().Colors[ImGuiCol_SliderGrab]            = slider_grab;
                    ImGui::GetStyle().Colors[ImGuiCol_SliderGrabActive]      = slider_grab_active;
                } else {
                    if(ImGui::Button("Play")) {
                        this->playMusic();
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

                            if(this->isSoundFXAutoPlay) {
                                this->playSoundFX();
                            }
                        }

                        if(is_selected) {
                            ImGui::SetItemDefaultFocus();
                        }
                    }
                    ImGui::EndCombo();
                }

                ImGui::Checkbox("Sound FX Auto Play", &this->isSoundFXAutoPlay);
                ImGui::SameLine();
                if(this->isSoundFXAutoPlay) {
                    ImGui::Checkbox("Is Sound FX Auto Play 2D?", &this->isSoundFXAutoPlay2D);
                    ImGui::SameLine();
                }
                ImGui::Checkbox("Sound FX Looping", &this->isSoundFXLooping);

                if(!this->isSoundFXLooping) {
                    ImGui::SliderInt("Amount of Repeats", &this->soundFXAmountOfRepeats, 1, 255);
                    ImGui::InputInt("Amount of Repeats: Input", &this->soundFXAmountOfRepeats);

                    if(this->soundFXAmountOfRepeats < 1) {
                        this->soundFXAmountOfRepeats = 1;
                    }
                    if(this->soundFXAmountOfRepeats > 255) {
                        this->soundFXAmountOfRepeats = 255;
                    }
                }

                // distanceScaled slider
                ImGui::SliderFloat("Distance Scaled", &soundFXPlayer.scaledDistance, 255.0f, 4096.0f);

                if(!soundFXPlayer.isPlaying()) {
                    if(ImGui::Button("Play")) {
                        if(isSoundFXLooping) {
                            soundFXPlayer.play(-1, -1);
                        } else {
                            soundFXPlayer.play(-1, this->soundFXAmountOfRepeats - 1);
                        }
                    }
                    ImGui::SameLine();
                    if(ImGui::Button("Play 2D")) {
                        if(isSoundFXLooping) {
                            soundFXPlayer.play(-1, -1, true);
                        } else {
                            soundFXPlayer.play(-1, this->soundFXAmountOfRepeats - 1, true);
                        }
                    }
                } else {
                    if(ImGui::Button("Stop")) {
                        soundFXPlayer.stop();
                    }
                }

                ImGui::PopID();
        }

        void font_player_configuration() {
            // Player Sections

            ImGui::Text("Player Configuration");
            ImGui::PushID("player_section");

            ImGui::Checkbox("Array Test", &this->isArrayTest);
            ImGui::Checkbox("Player Warp: (hold left ctrl to prevent teleport)", &this->isPlayerWarp);
            ImGui::PopID();
            ImGui::Separator();
            ImGui::Text("Font Configuration");
            ImGui::PushID("font_section");
            ImGui::ColorEdit3("Font Color", &this->fontColor[0]);
            ImGui::PopID();
        }

        void renderMenu() {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();

            ImGui::NewFrame();
            ImGui::Begin("Configuration");

            ImGui::BeginTabBar("Configuration Tab Bar");

            if(ImGui::BeginTabItem("Sound Configuration")) {
                sound_configuration();
                ImGui::EndTabItem();
            }

            if(ImGui::BeginTabItem("Player/Font Configuration")) {
                font_player_configuration();
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();

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

            render::font_postprocess::setColor(this->fontColor);

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