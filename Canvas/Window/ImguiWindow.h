#ifndef _CC_IMGUI_WINDOW_H
#define _CC_IMGUI_WINDOW_H

#include "Types.h"
#include "RGB.h"

#include <string>

struct GLFWwindow;

namespace cc
{
    class ImguiWindow
    {
    public:
        ImguiWindow(const std::string& title = "ImGui Window", int32_t width = 640, int32_t height = 480);

        void BeginFrame();
        void EndFrame();

        void Close();
        bool IsClosed() const;

        void SetAsCurrent();

        void SetSize(int32_t width, int32_t height);
        int32_t GetWidth() const;
        int32_t GetHeight() const;

        void SetTitle(const std::string& title);

        void SetClearColour(const RGBA& clearColour);

        virtual ~ImguiWindow();
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
