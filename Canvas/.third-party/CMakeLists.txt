set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("stb-image")
add_subdirectory("glfw-3.3.7")
add_subdirectory("glad")
add_subdirectory("imgui-1.87")
