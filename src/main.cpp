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

        // Box
        physics::Body boxBody;
        physics::Shape boxShape;

        // Player
        physics::Body playerBody;
        physics::Shape playerShape;

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

            physics::setGravity(cpv(0.0f, -100.0f));

            // Platform
            platBody.setBodyType(physics::BodyType::BT_STATIC);
            platBody.init();
            platBody.setPosition(cpv(320.0f, -(12.0f * 32.0f)));

            platShape.initBox(&platBody, 32.0f * 16.0f, 32.0f);
            platShape.setFriction(0.5f);
            physics::addShape(&platShape);

            // Box
            boxBody.setBodyType(physics::BodyType::BT_DYNAMIC);
            boxBody.setMass(1.0f);
            boxBody.setMoment(physics::toBoxMoment(1.0f, 32.0f, 32.0f));
            boxBody.init();
            boxBody.setPosition(cpv(128.0f, -32.0f));
            boxBody.setAngle(glm::radians(45.0f));

            physics::addBody(&boxBody);

            boxShape.initBox(&boxBody, 32.0f, 32.0f);
            boxShape.setFriction(0.5f);
            physics::addShape(&boxShape);

            // Player
            
        }

        virtual void handleEvent(SDL_Event* e) {
            ImGui_ImplSDL2_ProcessEvent(e);
        }

        virtual void update(float delta) {

            physics::step(1.0f / 60.0f);

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

        void renderMenu() {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();

            ImGui::NewFrame();
            ImGui::Begin("Configuration");

            ImGui::Text("Physics System Controls");

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
            drawTexture(this->box_tex, glm::vec2(p.x, -p.y), r, glm::vec2(32.0f, 32.0f));

            p = this->platBody.getPosition();

            // Draw Brick
            drawTexture(this->brick_tex, glm::vec2(p.x, -p.y), 0.0f, glm::vec2(32.0f * 16.0f, 32.0f));

            // Draw Player
            drawTexture(this->icon_32, this->postion, 0.0f, glm::vec2(32.0f, 32.0f));
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

            // Player
            // Box
            physics::removeShape(&this->boxShape);
            physics::removeBody(&this->boxBody);
            this->boxShape.release();
            this->boxBody.release();

            // Platform
            physics::removeShape(&this->platShape);
            platShape.release();
            platBody.release();

            icon_array_texCoords.release();
            icon_array.release();
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