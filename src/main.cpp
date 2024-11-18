#include "chipmunk/chipmunk_types.h"
#include "engine/app/app.h"
#include "engine/input/input.h"
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
#include "thirdparty/imgui/imgui.h"
#include "thirdparty/imgui/imgui_impl_sdl2.h"
#include "thirdparty/imgui/imgui_impl_opengl3.h"

struct TestApplication : public app::IApplication {
        int i = 0;

        render::glw::Texture2D icon_32;
        render::glw::Texture2D box_tex;
        render::glw::Texture2D brick_tex;
        render::glw::Texture2D ball_tex;

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

        input::InputMapping moveLeft;
        input::InputMapping moveRight;

        input::InputMapping jumpIM;

        virtual void init() {

            IMGUI_CHECKVERSION();

            ImGui::CreateContext();
            
            // If I need it
            ImGuiIO& io = ImGui::GetIO();

            ImGui::StyleColorsDark();

            ImGui_ImplSDL2_InitForOpenGL(app::getWindow(), app::getContext());
            ImGui_ImplOpenGL3_Init("#version 400");


            render::glw::Texture2D::createTexture2DFromFile(&icon_32, "data/icon/icon_32.png");
            render::glw::Texture2D::createTexture2DFromFile(&this->box_tex, "data/icon/Box.png");
            render::glw::Texture2D::createTexture2DFromFile(&this->brick_tex, "data/icon/Brick.png");
            render::glw::Texture2D::createTexture2DFromFile(&this->ball_tex, "data/icon/Ball.png");

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

            input::initInputMapping(moveLeft, input::Keyboard::KEYS_LEFT);
            input::initInputMapping(moveRight, input::Keyboard::KEYS_RIGHT);
            input::initInputMapping(jumpIM, input::Keyboard::KEYS_SPACE);

        }

        virtual void handleEvent(SDL_Event* e) {
            ImGui_ImplSDL2_ProcessEvent(e);
        }

        virtual void update(float delta) {
            float speed = 64.0f;
            float jump = 32.0f * 4.0f;
            //cpVect vel = playerBody.getVelocity();
            cpVect vel = playerBody.getVelocity();

            vel.x = input::getInputMappingAxisPressed(moveLeft, moveRight);
            vel.y += jump * input::getInputMappingValuePressedOnce(jumpIM);

            if(input::gamepad::isControllerConnected(input::gamepad::PlayerControllerName::PCN_PLAYER_1)) {

                //vel.x = input::gamepad::getLeftAxis(input::gamepad::PlayerControllerName::PCN_PLAYER_1).x;

                glm::vec2 leftAxis = input::gamepad::getLeftAxis(input::gamepad::PlayerControllerName::PCN_PLAYER_1);

                std::cout << leftAxis.x << ", " << leftAxis.y << "\n";

                vel.x += leftAxis.x;
                
                if(input::gamepad::isButtonPressedOnce(input::gamepad::PlayerControllerName::PCN_PLAYER_1, input::gamepad::ControllerButton::CB_A)) {
                    vel.y += jump;
                }
            }


            vel.x *= speed;

            playerBody.setVelocity(vel);
            playerBody.setAngularVelocity(0.0f);
            playerBody.setAngle(0.0f);

            physics::step(1.0f / 60.0f);

            gravity.x = g.x;
            gravity.y = g.y;

            physics::setGravity(gravity);

            glm::vec2 w = input::getMouseWheel();

            std::cout << w.x << ", " << -w.y << "\n";

        }

        void renderMenu() {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();

            ImGui::NewFrame();
            ImGui::Begin("Configuration");

            ImGui::Text("Physics System Controls");

            ImGui::SliderFloat2("Gravity", &g[0], -100.0f, 100.0f);

            ImGui::End();

            ImGui::EndFrame();

            ImGui::Render();

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        void drawTexture(render::glw::Texture2D& tex, const glm::vec2& p, float r, const glm::vec2& s) {
            render::startShader(render::ShaderType::ST_MAIN);

            //render::setView(glm::mat4(1.0f));
            render::setModel(
                glm::translate(glm::mat4(1.0f), glm::vec3(p, 0.0f)) *
                glm::rotate(glm::mat4(1.0f), r, glm::vec3(0.0f, 0.0f, 1.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(s, 0.0f))
            );

            tex.bind(GL_TEXTURE0);
            render::draw_center();
            tex.unbind(GL_TEXTURE0);

            render::endShader();
        }

        virtual void render() {
            render::startFrame();

            render::clear(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

            render::setView(glm::mat4(1.0f));
            render::updateCameraBuffer();

            cpVect p = this->boxBody.getPosition();
            float r = this->boxBody.getAngle();

            // Draw Box
            drawTexture(this->box_tex, glm::vec2(p.x, -p.y), -r, glm::vec2(32.0f, 32.0f));

            p = this->ballBody.getPosition();
            r = this->ballBody.getAngle();

            // Draw Ball
            render::enableBlend();
            drawTexture(this->ball_tex, glm::vec2(p.x, -p.y), -r, glm::vec2(32.0f, 32.0f));
            render::disableBlend();

            p = this->platBody.getPosition();
            // Draw Brick
            drawTexture(this->brick_tex, glm::vec2(p.x, -p.y), 0.0f, glm::vec2(32.0f * 16.0f, 32.0f));

            // Wall Left
            p = this->leftWallBody.getPosition();
            
            // Draw Brick
            drawTexture(this->brick_tex, glm::vec2(p.x, -p.y), 0.0f, glm::vec2(32.0f, 288.0f));
            // Wall Right
            p = this->rightWallBody.getPosition();
            
            // Draw Brick
            drawTexture(this->brick_tex, glm::vec2(p.x, -p.y), 0.0f, glm::vec2(32.0f, 288.0f));

            p = this->ceilingBody.getPosition();
            // Draw Brick
            drawTexture(this->brick_tex, glm::vec2(p.x, -p.y), 0.0f, glm::vec2(32.0f * 16.0f, 32.0f));

            // Draw Player
            p = this->playerBody.getPosition();
            drawTexture(this->icon_32, glm::vec2(p.x, -p.y), 0.0f, glm::vec2(32.0f, 32.0f));
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

            icon_array_texCoords.release();
            icon_array.release();
            ball_tex.release();
            brick_tex.release();
            box_tex.release();
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