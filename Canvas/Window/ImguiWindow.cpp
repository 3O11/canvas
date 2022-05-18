#include "ImguiWindow.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

namespace cc
{
    ImguiWindow::ImguiWindow(const std::string& title, int32_t width, int32_t height)
        : m_width(width), m_height(height), m_closed(false)
    {
        glfwInit();

        glfwSetErrorCallback(error_callback);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        m_glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        glfwMakeContextCurrent(m_glfwWindow);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        glfwSwapInterval(1);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(m_glfwWindow, true);
        ImGui_ImplOpenGL3_Init("#version 150");
    }

    void ImguiWindow::BeginFrame()
    {
        glfwPollEvents();
        m_closed = glfwWindowShouldClose(m_glfwWindow);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImguiWindow::EndFrame()
    {
        ImGui::Render();
        glViewport(0, 0, m_width, m_height);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_glfwWindow);
    }

    void ImguiWindow::Close()
    {
        glfwSetWindowShouldClose(m_glfwWindow, true);
    }

    bool ImguiWindow::IsClosed() const
    {
        return m_closed;
    }

    void ImguiWindow::SetAsCurrent()
    {
        glfwMakeContextCurrent(m_glfwWindow);
    }

    void ImguiWindow::SetSize(int32_t width, int32_t height)
    {
        m_width = width;
        m_height = height;
        glfwSetWindowSize(m_glfwWindow, width, height);
        glViewport(0, 0, m_width, m_height);
    }

    int32_t ImguiWindow::GetWidth() const
    {
        return m_width;
    }

    int32_t ImguiWindow::GetHeight() const
    {
        return m_height;
    }

    void ImguiWindow::SetTitle(const std::string& title)
    {
        glfwSetWindowTitle(m_glfwWindow, title.c_str());
    }

    void ImguiWindow::SetClearColour(const RGBA& clearColour)
    {
        m_clearColour = clearColour;
        glClearColor(m_clearColour.r, m_clearColour.g, m_clearColour.b, m_clearColour.a);
    }

    ImguiWindow::~ImguiWindow()
    {
        ImGui_ImplGlfw_Shutdown();
        glfwDestroyWindow(m_glfwWindow);
        glfwTerminate();
    }
}
