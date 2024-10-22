#include "engine/app/app.h"
#include "engine/input/input.h"
#include "engine/render/glw/glw.h"
#include "engine/render/render.h"
#include "engine/sys.h"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/gtc/constants.hpp"
#include "thirdparty/imgui/imgui.h"
#include "thirdparty/imgui/imgui_impl_sdl2.h"
#include "thirdparty/imgui/imgui_impl_opengl3.h"
#include "json/value.h"
#include <json/json.h>
#include <fstream>
#include <functional>
#include <vector>


struct TestApplication : public app::IApplication {
        int i = 0;

        render::glw::Texture2D icon_32;
        render::glw::Texture2DArray icon_array;

        // Custom TexCoords for texture array example
        render::glw::VertexBuffer icon_array_texCoords;

        glm::vec2 postion = glm::vec2(32.0f);

        glm::vec2 velocity = glm::vec2(0.0f);

        float speed = 64.0f;

        bool isTextureLinear = true;

        bool isArrayTest = false;

        float pixelSize = 2.0f;

        bool enableScanlines = false;

        glm::vec4 scanlineColor;

        const char* example_items[8] = {
            "Regular",
            "Invert",
            "Greyscale",
            "Sepia",
            "Pixelate",
            "Invert Pixelate",
            "Greyscale Pixelate",
            "Sepia Pixelate"
        };

        const char* current_example_item = "Regular";

        virtual void init() {

            IMGUI_CHECKVERSION();

            ImGui::CreateContext();

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
        }

        void renderMenu() {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();

            ImGui::NewFrame();

            ImGui::Begin("Configuration");
            
            ImGui::Text("Main Controls");

            if(ImGui::Checkbox("Is Texture Linear", &this->isTextureLinear)) {
                //std::cout << "Hello, World\n";
                render::test::setTextureLinear(isTextureLinear);
            }

            ImGui::Checkbox("Array Test", &isArrayTest);

            if(ImGui::Checkbox("Enable Scanlines", &enableScanlines)) {
                render::test::setEnablescanlines(enableScanlines);
            }

            if(ImGui::BeginCombo("Example", current_example_item)) {
                for(int i = 0; i < IM_ARRAYSIZE(this->example_items); i++) {
                    bool is_selected = (current_example_item == example_items[i]);

                    if(ImGui::Selectable(example_items[i], is_selected)) {
                        current_example_item = example_items[i];
                        render::test::setExample((render::test::Example)i);
                    }
                    if(is_selected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }


            std::function<bool()> isPixelActivated = [&]() {

                return 
                    render::test::getExample() == render::test::Example::PIXELATE ||
                    render::test::getExample() == render::test::Example::INVERT_PIXELATE ||
                    render::test::getExample() == render::test::Example::GREYSCALE_PIXELATE ||
                    render::test::getExample() == render::test::Example::SEPIA_PIXELATE;
            };

            if(isPixelActivated()) {
                ImGui::Separator();
                ImGui::Text("Pixelation Controls");
                if(ImGui::SliderFloat("Pixel Size", &pixelSize, 1.0, 64.0)) {
                    render::test::setPixelSize(pixelSize);
                }
            }

            if(enableScanlines) {
                ImGui::Separator();

                ImGui::Text("Scanline Controls");

                if(ImGui::ColorPicker4("Scanline Color", &scanlineColor[0])) {
                    render::test::setScanlineColor(this->scanlineColor);
                }
            }

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
            render::endFrame();

            // The menu isn't appart of the frame...
            renderMenu();
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

    load_config(&config);
    config.app = &testApp;

    app::init(&config);
    app::update();
    app::release();

    return 0;
}