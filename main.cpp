#define GL_SILENCE_DEPRECATION

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>

void setupUI()
{
    static float sliderValue = 0.0f; // Value to adjust with slider
    static int counter = 0;          // Counter for button press
    static char inputText[128] = ""; // Input field for text
    static bool checkbox = false;    // Checkbox state

    ImGui::Begin("Interactive UI");                               // Create a new window
    ImGui::Text("This is a basic interactive UI");                // Static text
    ImGui::SliderFloat("Adjust Value", &sliderValue, 0.0f, 1.0f); // Slider
    if (ImGui::Button("Click Me"))                                // Button
        counter++;
    ImGui::SameLine();                                                  // Keep next item on the same line
    ImGui::Text("Count: %d", counter);                                  // Display counter value
    ImGui::Checkbox("Enable Option", &checkbox);                        // Checkbox
    ImGui::InputText("Input Text", inputText, IM_ARRAYSIZE(inputText)); // Input field
    ImGui::Text("Text Entered: %s", inputText);                         // Display entered text
    ImGui::End();                                                       // End the window
}

int main()
{
    // Initialize GLFW
    if (!glfwInit())
        return -1;

    // Create window with OpenGL context
    GLFWwindow *window = glfwCreateWindow(500, 500, "Blind Archers", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    // Setup ImGui backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 120");

    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported: " << version << std::endl;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Draw UI
        setupUI();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.9f, 0.1f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

        ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
