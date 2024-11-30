#include "GUI.hpp"

GUI::GUI(GLFWwindow *window) : window(window), sliderValue(0.0f), counter(0), checkbox(false)
{
    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    // Setup ImGui backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 150");

    // Clear input text buffer
    inputText[0] = '\0';
}

GUI::~GUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GUI::newFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUI::render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::setupUI()
{
    ImGui::Begin("Interactive UI");
    ImGui::Text("This is a basic interactive UI");
    ImGui::SliderFloat("Adjust Value", &sliderValue, 0.0f, 1.0f);
    if (ImGui::Button("Click Me"))
        counter++;
    ImGui::SameLine();
    ImGui::Text("Count: %d", counter);
    ImGui::Checkbox("Enable Option", &checkbox);
    ImGui::InputText("Input Text", inputText, IM_ARRAYSIZE(inputText));
    ImGui::Text("Text Entered: %s", inputText);
    ImGui::End();
}