add_library(imgui STATIC
    "imgui.h"
    "imgui.cpp"
    "imconfig.h"
    "imgui_internal.h"
    "imgui_draw.cpp"
    "imgui_demo.cpp"
    "imgui_tables.cpp"
    "imgui_widgets.cpp"
    "backends/imgui_impl_opengl3.h"
    "backends/imgui_impl_opengl3.cpp"
    "backends/imgui_impl_glfw.h"
    "backends/imgui_impl_glfw.cpp"
)

target_include_directories(imgui PUBLIC
    "."
)

target_link_libraries(imgui PRIVATE
    glfw
)