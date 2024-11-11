#include "chipmunk/chipmunk_types.h"
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
#include <chipmunk/chipmunk.h>

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

        cpVect gravity;
        cpSpace* space = nullptr;

        // Platform
        //cpBB* platform = nullptr;
        cpBB box;

        cpShape* platformShape = nullptr;
        cpBody* platformBody = nullptr;
        // Player
        // Box
        cpShape* boxShape = nullptr;
        cpBody* boxBody = nullptr;


        float time = 0.0f;
        float maxTime = 1.0f / 60.0f;

        bool isMouseEnabled = false;

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

            this->gravity = cpv(0.0f, 100.0f);

            this->space = cpSpaceNew();
            cpSpaceSetGravity(space, this->gravity);

            // Platform (64.0f, 32.0f * 12) [32.0f * 16.0f, 32.0f]
            platformBody = cpBodyNewStatic();
            cpBodySetPosition(platformBody, cpv(64.0f, (32.0f * 12.0f)));
            cpBodySetAngle(platformBody, 0.0f);
        
            box.l = 0.0f;
            box.r = 32.0f * 16.0f;
            box.t = 0.0f;
            box.b = -32.0f;

            std::cout << "Platform" << "\n";

            platformShape = cpBoxShapeNew2(this->platformBody, box, 1.0f);
            //platformShape = cpBoxShapeNew(this->platformBody, 32.0f * 16.0f, 32.0f, 1.0f);
            cpSpaceAddShape(this->space, this->platformShape);
            cpShapeSetFriction(this->platformShape, 1.0f);
            
            // Player
            
            // Box
            //cpFloat moment = cpMomentForBox(1.0f, 32.0f, 32.0f);
            cpFloat moment = cpMomentForBox2(1.0f, cpBBNew(0.0f, -32.0f, 32.0f, 0.0f));

            //this->boxBody = cpBodyNew(1.0f, moment);

            std::cout << "Box" << "\n";
            this->boxBody = cpSpaceAddBody(space, cpBodyNew(1.0f, moment));
            cpBodySetPosition(this->boxBody, cpv(128.0f, 32.0f));

            //this->boxShape = cpSpaceAddShape(space, cpBoxShapeNew(this->boxBody, 32.0f, 32.0f, 1.0f));
            this->boxShape = cpSpaceAddShape(space, cpBoxShapeNew2(boxBody, cpBBNew(0.0f, -32.0f, 32.0f, 0.0f), 1.0f));


            cpShapeSetFriction(this->boxShape, 0.7f);
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

            if(this->time >= this->maxTime) {
                //cpSpaceStep(space, 1.0f / 60.0f);
                this->time = 0.0f;
            } else {
                this->time += delta;
            }

            if(isMouseEnabled) {
                if(input::isMouseButtonPressedOnce(input::MouseButtons::MBS_LEFT) && !input::isKeyPressed(input::Keyboard::KEYS_LCTRL)) {
                    // Scale Mouse Position
                    float scaledWidth = (float)app::get_width() / (float)render::getWidth();
                    float scaledHeight = (float)app::get_height() / (float)render::getHeight();

                    glm::vec2 mp = input::getPosition();

                    glm::vec2 mc = glm::vec2(
                        mp.x / scaledWidth,
                        mp.y / scaledHeight
                    );

                    cpBodySetPosition(this->boxBody, cpv(mc.x, mc.y));
                    cpBodyActivate(this->boxBody);
                    
                }
            }
            cpSpaceStep(space, 1.0f / 60.0f);
        }

        void renderMenu() {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();

            ImGui::NewFrame();
            ImGui::Begin("Configuration");

            ImGui::Text("Physics System Controls");

            ImGui::Checkbox("Is Box Mouse Enabled", &this->isMouseEnabled);

            ImGui::End();

            ImGui::EndFrame();

            ImGui::Render();

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        void drawSprite(render::glw::Texture2D* tex, const glm::vec2& position, const glm::vec2& size, float zrot) {
            render::startShader(render::ShaderType::ST_MAIN);

            //render::setView(glm::mat4(1.0f));
            render::setModel(
                glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f)) *
                glm::rotate(glm::mat4(1.0f), glm::radians(zrot), glm::vec3(0.0f, 0.0f, 1.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(size, 0.0f))
            );

            tex->bind(GL_TEXTURE0);
            render::draw();
            tex->unbind(GL_TEXTURE0);

            render::endShader();
        }

        virtual void render() {
            render::startFrame();

            render::clear(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

            render::setView(glm::mat4(1.0f));
            render::updateCameraBuffer();

            cpVect p = cpBodyGetPosition(this->boxBody);

            this->drawSprite(&this->box_tex, glm::vec2(p.x, p.y), glm::vec2(32.0f), 0.0f);

            p = cpBodyGetPosition(this->platformBody);

            this->drawSprite(&this->brick_tex, glm::vec2(p.x, p.y), glm::vec2(32.0f * 16.0f, 32.0f), 0.0f);

            this->drawSprite(&this->icon_32, this->postion, glm::vec2(32.0f, 32.0f), 0.0f);

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
            cpSpaceRemoveShape(this->space, this->boxShape);
            cpSpaceRemoveBody(this->space, this->boxBody);
            cpSpaceRemoveShape(this->space, this->platformShape);

            cpShapeFree(this->boxShape);
            cpBodyFree(this->boxBody);

            cpShapeFree(this->platformShape);
            cpBodyFree(this->platformBody);
            // Freeing Chipmunk Stuff
            cpSpaceFree(this->space);
            // Forget to release textures :(
            box_tex.release();
            brick_tex.release();
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