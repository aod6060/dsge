#include "chipmunk/chipmunk_types.h"
#include "engine/app/app.h"
#include "engine/config/config.h"
#include "engine/igw/igw.h"
#include "engine/input/input.h"
#include "engine/lw/lw.h"
#include "engine/physics/physics.h"
#include "engine/render/font/font.h"
#include "engine/render/glw/glw.h"
#include "engine/render/render.h"
#include "engine/sound/sound.h"
#include "engine/sys.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/ext/vector_common.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/gtc/constants.hpp"
#include "glm/trigonometric.hpp"
#include <cmath>
#include <json/json.h>
#include "json/value.h"
#include <climits>
#include <sstream>
#include <vector>
#include "lauxlib.h"
#include "thirdparty/imgui/imgui.h"
#include "thirdparty/imgui/imgui_impl_sdl2.h"
#include "thirdparty/imgui/imgui_impl_opengl3.h"

struct TestApplication : public app::IApplication {
        int i = 0;

        // Custom TexCoords for texture array example
        //render::glw::VertexBuffer icon_array_texCoords;

        glm::vec2 postion = glm::vec2(32.0f);

        glm::vec2 velocity = glm::vec2(0.0f);

        float speed = 64.0f;

        glm::vec2 soundPosition;

        bool isArrayTest = false;

        int32_t width;
        int32_t height;

        // Platform
        physics::Body platBody;
        physics::Shape platShape;

        // Walls
        // Left
        physics::Body leftWallBody;
        physics::Shape leftWallShape;

        // Right
        physics::Body rightWallBody;
        physics::Shape rightWallShape;

        // Ceiling
        physics::Body ceilingBody;
        physics::Shape ceilingShape;

        // Box
        physics::Body boxBody;
        physics::Shape boxShape;

        // Player
        physics::Body playerBody;
        physics::Shape playerShape;

        // Ball
        physics::Body ballBody;
        physics::Shape ballShape;

        glm::vec2 g = glm::vec2(0.0f, -100.0f);

        cpVect gravity;

        input::gamepad::InputMapping jumpIMCtrl;

        sound::MusicPlayer jungle;
        sound::SoundFXPlayer lazer;

        lua_wrapper::LWState state;

        virtual void init() {
            render::texture2D_manager::loadFromFile("icon_32", "data/icon/icon_32.png");
            render::texture2D_manager::loadFromFile("box_tex", "data/icon/Box.png");
            render::texture2D_manager::loadFromFile("brick_tex", "data/icon/Brick.png");
            render::texture2D_manager::loadFromFile("ball_tex", "data/icon/Ball.png");

            render::texture2D_array_manager::loadFromFile("icon_array", {
                "data/icon/icon_32.png",
                "data/icon/icon_32_green.png",
                "data/icon/icon_32_blue.png",
                "data/icon/icon_32_magenta.png"
            });

            render::vertex_buffer_manager::add("icon_array_texCoords");
            render::vertex_buffer_manager::add3("icon_array_texCoords", 0.0f, 0.0f, 0.0f);
            render::vertex_buffer_manager::add3("icon_array_texCoords", 1.0f, 0.0f, 1.0f);
            render::vertex_buffer_manager::add3("icon_array_texCoords", 0.0f, 1.0f, 2.0f);
            render::vertex_buffer_manager::add3("icon_array_texCoords", 1.0f, 1.0f, 3.0f);
            render::vertex_buffer_manager::update("icon_array_texCoords");

            render::font::loadFont("regular", "data/font/londrina_sketch_regular.ttf", 64);

            sound::addMusicStream("jungle", "data/sound/music/jungle.mp3");
            sound::addSoundFXStream("lazer", "data/sound/sfx/lazer.wav");

            jungle.init("jungle");
            lazer.init("lazer");
            
            jungle.play(-1);


            gravity = cpv(0.0f, -100.0f);

            physics::setGravity(gravity);

            // Platform
            platBody.setBodyType(physics::BodyType::BT_STATIC);
            platBody.init();
            platBody.setPosition(cpv(320.0f, -(12.0f * 32.0f)));

            platShape.initBox(&platBody, 32.0f * 16.0f, 32.0f);
            platShape.setFriction(0.5f);
            physics::addShape(&platShape);

            // Walls
            // Left
            leftWallBody.setBodyType(physics::BodyType::BT_STATIC);
            leftWallBody.init();
            leftWallBody.setPosition(cpv(64.0f + 16.0f, -224.0f));
            leftWallShape.initBox(&leftWallBody, 32.0f, 288.0f);
            physics::addShape(&leftWallShape);

            // Right
            rightWallBody.setBodyType(physics::BodyType::BT_STATIC);
            rightWallBody.init();
            rightWallBody.setPosition(cpv(render::getWidth() - (64.0f + 16.0f), -224.0f));
            rightWallShape.initBox(&rightWallBody, 32.0f, 288.0f);
            physics::addShape(&rightWallShape);

            // Ceiling
            ceilingBody.setBodyType(physics::BodyType::BT_STATIC);
            ceilingBody.init();
            ceilingBody.setPosition(cpv(320.0f, -64.0f));
            ceilingShape.initBox(&ceilingBody, 32.0f * 16.0f, 32.0f);
            physics::addShape(&ceilingShape);

            // Box
            boxBody.setBodyType(physics::BodyType::BT_DYNAMIC);
            boxBody.setMass(1.0f);
            boxBody.setMoment(physics::toBoxMoment(1.0f, 32.0f, 32.0f));
            boxBody.init();
            boxBody.setPosition(cpv(128.0f, -288.0f));
            boxBody.setAngle(glm::radians(35.0f));

            physics::addBody(&boxBody);

            boxShape.initBox(&boxBody, 32.0f, 32.0f);
            boxShape.setFriction(0.5f);
            physics::addShape(&boxShape);

            // Player
            playerBody.setBodyType(physics::BodyType::BT_DYNAMIC);
            playerBody.setMass(1.0f);
            playerBody.setMoment(physics::toBoxMoment(1.0f, 32.0f, 32.0f));
            playerBody.init();
            playerBody.setPosition(cpv(256.0f, -288.0f));
            playerBody.setAngle(0.0f); // To keep the player from rotating set it to zero 
            physics::addBody(&this->playerBody);

            playerShape.initBox(&this->playerBody, 32.0f, 32.0f);
            playerShape.setFriction(0.5f);
            physics::addShape(&this->playerShape);

            // Ball
            ballBody.setBodyType(physics::BodyType::BT_DYNAMIC);
            ballBody.setMass(1.0f);
            ballBody.setMoment(physics::toCircleMoment(1.0f, 0.0f, 16.0f, cpv(0.0f, 0.0f)));
            ballBody.init();
            ballBody.setPosition(cpv(384.0f, -288.0f));
            ballBody.setAngle(0.0f);
            physics::addBody(&this->ballBody);

            ballShape.initCircle(&ballBody, 16.0f, cpv(0.0f, 0.0f));
            ballShape.setFriction(0.5f);
            ballShape.setElasticity(0.0f);
            physics::addShape(&ballShape);
            // In the update function

            input::gamepad::initInputMapping(&jumpIMCtrl, input::gamepad::PlayerControllerName::PCN_PLAYER_1, input::gamepad::ControllerButton::CB_A);


            float w_test = 1280.0f;
            float h_test = 720.0f;

            std::cout << w_test << ", " << h_test << "\n";

            float aspect = w_test / h_test;

            std::cout << "aspect: " << aspect << "\n";

            float h = 640.0f / aspect;

            std::cout << 640.0f << ", " << h << "\n";

            state.open("data/script/test_2.lua");

        }

        virtual void handleEvent(SDL_Event* e) {
            //ImGui_ImplSDL2_ProcessEvent(e);
        }

        virtual void update(float delta) {
            float speed = 64.0f;
            float jump = 32.0f * 4.0f;
            //cpVect vel = playerBody.getVelocity();
            cpVect vel = playerBody.getVelocity();

            //vel.x = input::getInputMappingAxisPressed(&config::getConfig()->input.mapping.at("move-left").mapping, &config::getConfig()->input.mapping.at("move-right").mapping) + input::gamepad::getLeftAxis(input::gamepad::PlayerControllerName::PCN_PLAYER_1).x;
            vel.x = input::getInputMappingAxisPressed("move-left", "move-right") + input::gamepad::getLeftAxis(input::gamepad::PlayerControllerName::PCN_PLAYER_1).x;
            //vel.y += jump * input::getInputMappingValuePressedOnce(&config::getConfig()->input.mapping.at("jump-im").mapping) + jump * input::gamepad::getInputMappingValuePressedOnce(&jumpIMCtrl);
            vel.y += jump * input::getInputMappingValuePressedOnce("jump-im") + jump * input::gamepad::getInputMappingValuePressedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_1, "jump-im-ctrl");

            vel.x *= speed;

            playerBody.setVelocity(vel);
            playerBody.setAngularVelocity(0.0f);
            playerBody.setAngle(0.0f);

            physics::step(1.0f / 60.0f);


            gravity.x = g.x;
            gravity.y = g.y;

            physics::setGravity(gravity);

            glm::vec2 w = input::getMouseWheel();

            if(input::isKeyPressedOnce(input::Keyboard::KEYS_TAB)) {
                isArrayTest = !isArrayTest;
            }

            if(input::isKeyPressedOnce(input::Keyboard::KEYS_1)) {
                lazer.play(-1, 0);
            }
        }

        void renderMenu() {
            igw::bind();

            ImGui::Begin("Configuration");

            ImGui::Text("Physics System Controls");

            ImGui::SliderFloat2("Gravity", &g[0], -100.0f, 100.0f);

            ImGui::End();

            ImGui::Begin("Test Lua");

            if(ImGui::Button("Reload")) {
                state.reload();
            }

            if(ImGui::Button("Call \"callme\" lua function")) {
                state.callFunction("callme");
            }

            if(ImGui::Button("Application Exit Test")) {
                state.callFunction("test_app_exit");
            }

            if(ImGui::Button("Test App Interface")) {
                state.callFunction("test_app_interface");
            }   

            for(int i = 0; i < state.exports.size(); i++) {
                if(state.exports[i].type == lua_wrapper::LWType::LWT_INTEGER) {
                    if(ImGui::DragInt(state.exports[i].name.c_str(), &state.exports[i].ivalue)) {
                        state.setInteger(state.exports[i].name, state.exports[i].ivalue);
                    }
                } else if(state.exports[i].type == lua_wrapper::LWType::LWT_NUMBER) {
                    if(ImGui::DragFloat(state.exports[i].name.c_str(), &state.exports[i].nvalue)) {
                        state.setNumber(state.exports[i].name, state.exports[i].nvalue);
                    }
                } else if(state.exports[i].type == lua_wrapper::LWType::LWT_BOOL) {
                    if(ImGui::Checkbox(state.exports[i].name.c_str(), &state.exports[i].bvalue)) {
                        state.setBoolean(state.exports[i].name, state.exports[i].bvalue);
                    }
                }
            }

            ImGui::End();

            if(config::drawConfigSystem()) {
                return;
            }

            igw::unbind();
        }

        void drawTexture(std::string name, const glm::vec2& p, float r, const glm::vec2& s) {
            render::startShader(render::ShaderType::ST_MAIN);

            //render::setView(glm::mat4(1.0f));
            render::setModel(
                glm::translate(glm::mat4(1.0f), glm::vec3(p, 0.0f)) *
                glm::rotate(glm::mat4(1.0f), r, glm::vec3(0.0f, 0.0f, 1.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(s, 0.0f))
            );

            //tex.bind(GL_TEXTURE0);
            render::texture2D_manager::bind(name, GL_TEXTURE0);
            render::draw_center();
            render::texture2D_manager::unbind(name, GL_TEXTURE0);
            //tex.unbind(GL_TEXTURE0);

            render::endShader();
        }

        void drawTextureArray(std::string name, const glm::vec2& p, float r, const glm::vec2& s) {
            render::startShader(render::ShaderType::ST_TEXTURE2D_ARRAY);
            render::setModel(
                glm::translate(glm::mat4(1.0f), glm::vec3(p, 0.0f)) *
                glm::rotate(glm::mat4(1.0f), r, glm::vec3(0.0f, 0.0f, 1.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(s, 0.0f))
            );

            render::texture2D_array_manager::bind(name, GL_TEXTURE0);
            //render::draw_center(this->icon_array_texCoords);
            render::draw_center("icon_array_texCoords");
            render::texture2D_array_manager::unbind(name, GL_TEXTURE0);

            render::endShader();
        }

        virtual void render() {
            render::startFrame();

            render::clear(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

            cpVect test = playerBody.getPosition();
            render::setView(
                glm::translate(glm::mat4(1.0f), glm::vec3(render::getWidth() * 0.5f, render::getHeight() * 0.5f, 0.0f)) *
                glm::translate(glm::mat4(1.0f), -glm::vec3(test.x, -test.y, 0.0f))
            );
            render::updateCameraBuffer();

            cpVect p = this->boxBody.getPosition();
            float r = this->boxBody.getAngle();

            // Draw Box
            drawTexture("box_tex", glm::vec2(p.x, -p.y), -r, glm::vec2(32.0f, 32.0f));

            p = this->ballBody.getPosition();
            r = this->ballBody.getAngle();

            // Draw Ball
            render::enableBlend();
            drawTexture("ball_tex", glm::vec2(p.x, -p.y), -r, glm::vec2(32.0f, 32.0f));
            render::disableBlend();

            p = this->platBody.getPosition();
            // Draw Brick
            drawTexture("brick_tex", glm::vec2(p.x, -p.y), 0.0f, glm::vec2(32.0f * 16.0f, 32.0f));

            // Wall Left
            p = this->leftWallBody.getPosition();
            
            // Draw Brick
            drawTexture("brick_tex", glm::vec2(p.x, -p.y), 0.0f, glm::vec2(32.0f, 288.0f));
            // Wall Right
            p = this->rightWallBody.getPosition();
            
            // Draw Brick
            drawTexture("brick_tex", glm::vec2(p.x, -p.y), 0.0f, glm::vec2(32.0f, 288.0f));

            p = this->ceilingBody.getPosition();
            // Draw Brick
            drawTexture("brick_tex", glm::vec2(p.x, -p.y), 0.0f, glm::vec2(32.0f * 16.0f, 32.0f));

            // Draw Player

            if(this->isArrayTest) {
                p = this->playerBody.getPosition();
                drawTextureArray("icon_array", glm::vec2(p.x, -p.y), 0.0f, glm::vec2(32.0f, 32.0f));
                render::endFrame();
            } else {
                p = this->playerBody.getPosition();
                drawTexture("icon_32", glm::vec2(p.x, -p.y), 0.0f, glm::vec2(32.0f, 32.0f));
                render::endFrame();
            }

            
            std::stringstream ss;

            ss << "Position: [" << p.x << ", " << -p.y << "]";

            render::font::getSize("regular", ss.str(), &width, &height);
            render::font::update("regular", ss.str());

            render::font_postprocess::bind();
            render::enableBlend();

            render::font_postprocess::setProjection(glm::ortho(0.0f, (float)app::getWidth(), (float)app::getHeight(), 0.0f));
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
            state.close();

            // Ball
            physics::removeShape(&this->ballShape);
            physics::removeBody(&this->ballBody);
            this->ballShape.release();
            this->ballBody.release();

            // Player
            physics::removeShape(&this->playerShape);
            physics::removeBody(&this->playerBody);
            this->playerShape.release();
            this->playerBody.release();

            // Box
            physics::removeShape(&this->boxShape);
            physics::removeBody(&this->boxBody);
            this->boxShape.release();
            this->boxBody.release();

            // Ceiling
            physics::removeShape(&this->ceilingShape);
            ceilingShape.release();
            ceilingBody.release();

            // Walls
            // Left
            physics::removeShape(&this->leftWallShape);
            this->leftWallShape.release();
            this->leftWallBody.release();

            // Right
            physics::removeShape(&this->rightWallShape);
            this->rightWallShape.release();
            this->rightWallBody.release();

            // Platform
            physics::removeShape(&this->platShape);
            platShape.release();
            platBody.release();
        }

};

int main(int argc, char** argv) { 
    TestApplication testApp;

    app::init(&testApp);
    app::update();
    app::release();

    return 0;
}