#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_math.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_world.h"
#include "box2d/b2_world_callbacks.h"
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
#include <box2d/box2d.h>



struct ContactListener : public b2ContactListener {
	/// Called when two fixtures begin to touch.
	virtual void BeginContact(b2Contact* contact) { 

        //contact->GetFixtureA()->GetBody()

        if(contact->GetFixtureA()->IsSensor()) {
            std::cout << "Fixture A is Sensor start" << "\n";
        }
    }

	/// Called when two fixtures cease to touch.
	virtual void EndContact(b2Contact* contact) {
        if(contact->GetFixtureA()->IsSensor()) {
            std::cout << "Fixture A is Sensor end" << "\n";
        }
    }

	/// This is called after a contact is updated. This allows you to inspect a
	/// contact before it goes to the solver. If you are careful, you can modify the
	/// contact manifold (e.g. disable contact).
	/// A copy of the old manifold is provided so that you can detect changes.
	/// Note: this is called only for awake bodies.
	/// Note: this is called even when the number of contact points is zero.
	/// Note: this is not called for sensors.
	/// Note: if you set the number of contact points to zero, you will not
	/// get an EndContact callback. However, you may get a BeginContact callback
	/// the next step.
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
	}

	/// This lets you inspect a contact after the solver is finished. This is useful
	/// for inspecting impulses.
	/// Note: the contact manifold does not include time of impact impulses, which can be
	/// arbitrarily large if the sub-step is small. Hence the impulse is provided explicitly
	/// in a separate data structure.
	/// Note: this is only called for contacts that are touching, solid, and awake.
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	{
	}
};

struct TestApplication : public app::IApplication {
        int i = 0;

        // This variable will be used to determine what a meter is...
        // 1meter = 32pixels in the engine. So 1 meter is the size
        // of a whole tile.

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

        ContactListener contentListener;

        float meterToPixel(float meter) {
            return meter * 32.0f;
        }

        float pixelToMeter(float pixel) {
            return pixel / 32.0f;
        }

        glm::vec2 toGLMPosition(const b2Vec2& v) {
            return glm::vec2(
                meterToPixel(v.x),
                -meterToPixel(v.y)
            );
        }

        b2Vec2 toBox2DPosition(const glm::vec2& v) {
            return b2Vec2(
                pixelToMeter(v.x),
                -pixelToMeter(v.y)
            );
        }

        glm::vec2 toGLMSize(const b2Vec2& v) {
            return glm::vec2(
                meterToPixel(v.x),
                meterToPixel(v.y)
            );
        }

        b2Vec2 toBox2DSize(const glm::vec2& v) {
            return b2Vec2(
                pixelToMeter(v.x),
                pixelToMeter(v.y)
            );
        }

        b2World* world = nullptr;
        b2Vec2 gravity = b2Vec2(0.0f, -10.0f);

        // Ground
        b2BodyDef groundDef;
        b2Body* groundBody;
        b2PolygonShape groundShape;

        // Player
        b2BodyDef playerDef;
        b2Body* playerBody;
        b2PolygonShape playerShape;

        // Box
        b2BodyDef boxDef;
        b2Body* boxBody;
        b2PolygonShape boxShape;

        float time = 0.0f;
        float maxTime = 1.0f / 60.0f;

        float jump = 5.0f;

        bool isClickBox = false;

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
            

            this->world = new b2World(this->gravity);

            this->world->SetContactListener(&this->contentListener);
            
            // Create Ground
            glm::vec2 pixelSize = glm::vec2(32.0f * 16.0f, 32.0f) / 2.0f;
            this->groundDef.position = b2Vec2(this->toBox2DPosition(glm::vec2(320.0f, 384.0f)));
            this->groundDef.type = b2_staticBody;
            this->groundBody = world->CreateBody(&this->groundDef);

            b2Vec2 size = this->toBox2DSize(pixelSize);

            this->groundShape.SetAsBox(size.x, size.y);
            this->groundBody->CreateFixture(&this->groundShape, 0.0f);
            
            // Create Player
            this->playerDef.position = b2Vec2(this->toBox2DPosition(glm::vec2(32.0f, 32.0f)));
            this->playerDef.type = b2_dynamicBody;

            this->playerBody = world->CreateBody(&this->playerDef);

            size = this->toBox2DSize(glm::vec2(16.0f, 16.0f));

            this->playerShape.SetAsBox(size.x, size.y);

            b2FixtureDef fd;
            fd.shape = &this->playerShape;
            fd.density = 1.0f;
            fd.friction = 0.3f;
            fd.isSensor = false;

            this->playerBody->SetEnabled(true);
            this->playerBody->SetAwake(true);
            this->playerBody->SetSleepingAllowed(false);

            this->playerBody->CreateFixture(&fd);

            // Create Box
            this->boxDef.position = b2Vec2(this->toBox2DPosition(glm::vec2(128.0f, 32.0f) + glm::vec2(16.0f, 16.0f)));
            this->boxDef.type = b2_dynamicBody;

            this->boxBody = world->CreateBody(&this->boxDef);
            size = this->toBox2DSize(glm::vec2(16.0f, 16.0f));

            this->boxShape.SetAsBox(size.x, size.y);


            fd.shape = &this->boxShape;
            fd.density = 1.0f;
            fd.friction = 0.3f;
            fd.isSensor = false;

            this->boxBody->CreateFixture(&fd);
            
            //this->boxBody->CreateFixture(&this->boxShape, 1.0f);
        }

        virtual void handleEvent(SDL_Event* e) {
            ImGui_ImplSDL2_ProcessEvent(e);
        }

        virtual void update(float delta) {
            if(input::isKeyPressedOnce(input::Keyboard::KEYS_TAB)) {
                isArrayTest = !isArrayTest;
            }

            world->Step(1.0f / 60.0f, 8, 3);

            if(isClickBox && input::isMouseButtonPressedOnce(input::MouseButtons::MBS_LEFT) && !(input::isKeyPressed(input::Keyboard::KEYS_LCTRL))) {
                glm::vec2 mc = input::getConvertedPosition();

                b2Vec2 pmc = this->toBox2DPosition(mc);


                boxBody->SetTransform(pmc, 0.0f);
                boxBody->SetAwake(true);
            }

            b2Vec2 vel = this->playerBody->GetLinearVelocity();

            // Horizontal
            if(input::isKeyPressed(input::Keyboard::KEYS_LEFT)) {
                vel.x = -3;
            } else if(input::isKeyPressed(input::Keyboard::KEYS_RIGHT)) {
                vel.x = 3;
            } else {
                vel.x = 0;
            }

            if(input::isKeyPressedOnce(input::Keyboard::KEYS_SPACE)) {
                vel.y = jump;
            }

            // Vertical
            /*
            if(input::isKeyPressed(input::Keyboard::KEYS_UP)) {
                vel.y = 3;
            } else if(input::isKeyPressed(input::Keyboard::KEYS_DOWN)) {
                vel.y = -3;
            } else {
                vel.y = 0;
            }
            */

            // Normalize Velocity so it goes the same speed in the diaganal
            /*
            if(this->velocity != glm::zero<glm::vec2>()) {
                this->velocity = glm::normalize(this->velocity);
            }
            */
            // Add it to the postion
            //this->postion += velocity * speed * delta;

            this->playerBody->SetLinearVelocity(vel);
        }

        void renderMenu() {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();

            ImGui::NewFrame();
            ImGui::Begin("Configuration");

            ImGui::Text("Physics System Controls");

            ImGui::Text("Position in Pixels: [%f, %f]", this->postion.x, this->postion.y);

            b2Vec2 mp = this->toBox2DPosition(this->postion);

            ImGui::Text("Position in Meters: [%f, %f]", mp.x, mp.y);

            ImGui::SliderFloat("Jump", &this->jump, 1.0f, 20.0f);
            ImGui::Checkbox("Is Click Box Location?", &this->isClickBox);
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

            // Draw Box
            render::startShader(render::ShaderType::ST_MAIN);

            render::setModel(
                glm::translate(glm::mat4(1.0f), glm::vec3(this->toGLMPosition(this->boxBody->GetPosition()), 0.0f)) *
                glm::rotate(glm::mat4(1.0f), glm::radians(this->boxBody->GetAngle()), glm::vec3(0.0f, 0.0f, 1.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(32.0f, 32.0f, 0.0f))
            );

            box_tex.bind(GL_TEXTURE0);
            render::draw_center();
            box_tex.unbind(GL_TEXTURE0);

            // Draw Brick
            glm::vec2 pixelSize = glm::vec2(32.0f * 16.0f, 32.0f) / 2.0f;

            render::setModel(
                glm::translate(glm::mat4(1.0f), glm::vec3(this->toGLMPosition(this->groundBody->GetPosition()), 0.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(32.0f* 16.0f, 32.0f, 0.0f))
            );

            brick_tex.bind(GL_TEXTURE0);
            render::draw_center();
            brick_tex.unbind(GL_TEXTURE0);


            //render::setView(glm::mat4(1.0f));
            render::setModel(
                glm::translate(glm::mat4(1.0f), glm::vec3(this->toGLMPosition(this->playerBody->GetPosition()), 0.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(32.0f, 32.0f, 0.0f))
            );

            icon_32.bind(GL_TEXTURE0);
            render::draw_center();
            icon_32.unbind(GL_TEXTURE0);

            render::endShader();
            
            render::endFrame();

            
            std::stringstream ss;

            postion = this->toGLMPosition(this->playerBody->GetPosition());
            
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
            this->world->DestroyBody(this->boxBody);
            this->world->DestroyBody(this->playerBody);
            this->world->DestroyBody(this->groundBody);

            delete this->world;

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