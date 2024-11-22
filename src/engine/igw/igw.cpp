#include "igw_internal.h"


namespace igw {

    void init() {
        IMGUI_CHECKVERSION();

        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();

        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForOpenGL(app::getWindow(), app::getContext());
        ImGui_ImplOpenGL3_Init("#version 400");

    }

    void handleEvent(SDL_Event* e) {
        ImGui_ImplSDL2_ProcessEvent(e);
    }

    void release() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void bind() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();

        ImGui::NewFrame();
    }

    void unbind() {
        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void reloadInit() {
        IMGUI_CHECKVERSION();
        std::cout << "ImGui Check Version.\n";

        ImGui::CreateContext();
        std::cout << "ImGui Create Context\n";

        ImGuiIO& io = ImGui::GetIO();
        std::cout << "ImGui Grab IO\n";

        ImGui::StyleColorsDark();
        std::cout << "StyleColorsDark()\n";

        ImGui_ImplSDL2_InitForOpenGL(app::getWindow(), app::getContext());
        std::cout << "ImGui_ImplSDL2_InitForOpenGL(window, context)\n";

        ImGui_ImplOpenGL3_Init("#version 400");
        std::cout << "ImGui_ImplOpenGL3_Init(glsl_version)\n";
        
    }

    void reloadRelease() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

}