#include "ImguiWindow.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

namespace cc
{
    ImguiWindow::ImguiWindow(const std::string& title, int32_t width, int32_t height)
        : Window(title, width, height)
    {
        glfwMakeContextCurrent(m_glfwWindow);

        IMGUI_CHECKVERSION();
        m_windowContext = ImGui::CreateContext();

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(m_glfwWindow, true);
        ImGui_ImplOpenGL3_Init();
    }

    void ImguiWindow::BeginFrame()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImguiWindow::EndFrame()
    {
        ImGui::Render();
        glViewport(0, 0, m_width, m_height);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    ImguiWindow::~ImguiWindow()
    {
        ImGui_ImplGlfw_Shutdown();
    }
}
