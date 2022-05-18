#include "Window.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace cc
{
    Window::Window(const std::string& title, int32_t width, int32_t height)
        : m_width(width), m_height(height), m_closed(false), m_clearColour(), m_glfwWindow(nullptr)
    {
        if (!s_windowCount++)
        {
            glfwInit();
        }

        m_glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        glfwMakeContextCurrent(m_glfwWindow);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }

    void Window::BeginFrame()
    { 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();
    }

    void Window::EndFrame()
    {
        m_closed = glfwWindowShouldClose(m_glfwWindow);
        glfwSwapBuffers(m_glfwWindow);
    }

    void Window::Close()
    {
        glfwSetWindowShouldClose(m_glfwWindow, true);
        m_closed = true;
    }

    bool Window::IsClosed() const
    {
        return m_closed;
    }

    void Window::SetAsCurrent()
    {
        glfwMakeContextCurrent(m_glfwWindow);
    }

    void Window::SetSize(int32_t width, int32_t height)
    {
        m_width = width;
        m_height = height;
        glfwSetWindowSize(m_glfwWindow, width, height);
    }

    int32_t Window::GetWidth() const
    {
        return m_width;
    }

    int32_t Window::GetHeight() const
    {
        return m_height;
    }

    void Window::SetTitle(const std::string& title)
    {
        glfwSetWindowTitle(m_glfwWindow, title.c_str());
    }

    void Window::SetClearColour(const RGBA& clearColour)
    {
        glClearColor(m_clearColour.r, m_clearColour.g, m_clearColour.b, m_clearColour.a);
        m_clearColour = clearColour;
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_glfwWindow);

        if (!--s_windowCount)
        {
            glfwTerminate();
        }
    }

    int32_t Window::s_windowCount = 0;
}
