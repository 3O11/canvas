#ifndef _CC_BASE_WINDOW_H
#define _CC_BASE_WINDOW_H

#include <glad/glad.h>

#include <string>
#include <cstdint>

#include "RGB.h"

struct GLFWwindow;

namespace cc
{
    class Window
    {
    public:
        Window(const std::string& title, int32_t width = 640, int32_t height = 480);

        virtual void BeginFrame();
        virtual void EndFrame();

        void Close();
        bool IsClosed() const;

        void SetAsCurrent();

        void SetSize(int32_t width, int32_t height);
        int32_t GetWidth() const;
        int32_t GetHeight() const;

        void SetTitle(const std::string& title);

        void SetClearColour(const RGBA& clearColour);

        virtual ~Window();

    protected:
        int32_t      m_width;
        int32_t      m_height;
        bool         m_closed;
        RGBA         m_clearColour;
        GLFWwindow * m_glfwWindow;

    private:
        static int32_t s_windowCount;
    };
}

#endif //_CC_BASE_WINDOW_H
