// GUI.cpp
#include "GUI.hpp"

GUI::GUI(GLFWwindow* window) : window(window), sliderValue(0.0f), counter(0), checkbox(false), damage(0),hp(5){
    IMGUI_CHECKVERSION();
    context = ImGui::CreateContext();
    ImGui::SetCurrentContext(context);
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 150");

    inputText[0] = '\0';
}

GUI::~GUI() {
    ImGui::SetCurrentContext(context);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(context);
}

void GUI::newFrame() {
    ImGui::SetCurrentContext(context);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUI::render() {
    ImGui::SetCurrentContext(context);
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::setupUI() {
    ImGui::SetCurrentContext(context);
    ImGui::Begin("Archer");
    ImGui::Text("Current Archer Stats");
    if (ImGui::Button("Inflict Damage")){
        damage++;
    }
    ImGui::Text("Damage Dealt: %d", damage);
    ImGui::Text("Current HP : %d", hp);
    ImGui::Checkbox("Enable Option", &checkbox);
    ImGui::End();
}