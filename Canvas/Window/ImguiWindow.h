#ifndef _CC_IMGUI_WINDOW_H
#define _CC_IMGUI_WINDOW_H

#include <glad/glad.h>
#include <imgui.h>

#include "Window.h"

namespace cc
{
    class ImguiWindow : public Window
    {
    public:
        ImguiWindow(const std::string& title = "ImGui Window", int32_t width = 640, int32_t height = 480);

        void BeginFrame() override;
        void EndFrame() override;

        ~ImguiWindow();
    protected:
        ImGuiContext * m_windowContext;
    private:
    };
}

#endif //_CC_IMGUI_WINDOW_H
