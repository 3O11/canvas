#ifndef _CC_IMGUI_WINDOW_H
#define _CC_IMGUI_WINDOW_H

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include "Types.h"
#include "RGB.h"

#include <string>

namespace cc
{
    namespace detail
    {
        static void error_callback(int error, const char* description)
        {
            fprintf(stderr, "Error: %s\n", description);
        }
    }

    class ImguiWindow
    {
    public:
        ImguiWindow(const std::string& title = "ImGui Window", int32_t width = 640, int32_t height = 480)
            : m_width(width), m_height(height), m_closed(false)
        {
            glfwSetErrorCallback(detail::error_callback);

            glfwInit();

            m_glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

            glfwMakeContextCurrent(m_glfwWindow);
            gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            glfwSwapInterval(1);

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;

            ImGui::StyleColorsDark();

            ImGui_ImplGlfw_InitForOpenGL(m_glfwWindow, true);
            ImGui_ImplOpenGL3_Init();
        }

        void BeginFrame()
        {
            glfwPollEvents();
            m_closed = glfwWindowShouldClose(m_glfwWindow);
            glfwGetWindowSize(m_glfwWindow, &m_width, &m_height);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        void EndFrame()
        {
            ImGui::Render();
            glViewport(0, 0, m_width, m_height);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(m_glfwWindow);
        }

        void Close()
        {
            glfwSetWindowShouldClose(m_glfwWindow, true);
        }

        bool IsClosed() const
        {
            return m_closed;
        }

        void SetAsCurrent()
        {
            glfwMakeContextCurrent(m_glfwWindow);
        }

        void SetSize(int32_t width, int32_t height)
        {
            m_width = width;
            m_height = height;
            glfwSetWindowSize(m_glfwWindow, width, height);
            glViewport(0, 0, m_width, m_height);
        }

        int32_t GetWidth() const
        {
            return m_width;
        }

        int32_t GetHeight() const
        {
            return m_height;
        }

        void SetTitle(const std::string& title)
        {
            glfwSetWindowTitle(m_glfwWindow, title.c_str());
        }

        void SetClearColour(const RGBA& clearColour)
        {
            m_clearColour = clearColour;
            glClearColor(m_clearColour.r, m_clearColour.g, m_clearColour.b, m_clearColour.a);
        }

        virtual ~ImguiWindow()
        {
            ImGui_ImplGlfw_Shutdown();
            glfwDestroyWindow(m_glfwWindow);
            glfwTerminate();
        }

    protected:
        int32_t        m_width;
        int32_t        m_height;
        bool           m_closed;
        RGBA           m_clearColour;
        GLFWwindow   * m_glfwWindow;
    private:
    };
}

#endif //_CC_IMGUI_WINDOW_H
