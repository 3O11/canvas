#include "Window.h"
#include "ImguiWindow.h"

#include "RGB.h"

int main()
{
    {
        cc::ImguiWindow window;

        window.SetClearColour({1.0f, 0.0f, 0.5f, 1.0f});

        bool demo_window = true;
        cc::RGBA bg_colour = {0.5f, 0.5f, 0.5f};

        while(!window.IsClosed())
        {
            window.BeginFrame();

            ImGui::ShowDemoWindow(&demo_window);

            ImGui::Begin("Edit Background");

            ImGui::ColorEdit3("bg", (float*)&bg_colour);
            window.SetClearColour(bg_colour);

            ImGui::End();

            window.EndFrame();
        }
    }

    {
        cc::Window window;

        window.SetClearColour({0.0f, 1.0, 0.5f, 1.0f});

        while (!window.IsClosed())
        {
            window.Update();
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
            window.SwapBuffers();
        }
    }
}
