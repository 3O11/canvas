# canvas

## Purpose

This is a small personal project to enable quick and easy showcases of
various computer graphics techniques and effects.

## Examples

The examples directory contains various showcases of the functionality provided
by the canvas library. The tools provided by the library are still very limited,
so there isn't yet much to show.

## Documentation

The documentation of this project is currently severely lacking,
because there is none. This should change as soon as I have more time to
work on the QoL things around this codebase.

## Usage

If you want to use this library, despite the limited functionality and lack of
documentation and tests. It should be as simple as cloning this directory into your
own project and linking it via CMake:
```cmake
target_link_libraries ($YOUR_PROJECT PRIVATE canvas)
```

The library works under Windows. It does compile on Mac, but I haven't had much
luck trying to figure out the versioning of OpenGL under Mac (mostly related to ImGui
failing to load its OpenGL bindings). The library is as of yet untested under Linux,
but in theory there should be no problems with compiling and running the code there.

## Acknowledgement

I am not the author of any of the code in the .third-party directory,
except for a few CMakeLists.txt files that were created for easier integration of
third-party libraries into the canvas library. The libraries used in this project are:

- [stb_image and stb_image_write](https://github.com/nothings/stb)
- [GLFW](https://github.com/glfw/glfw) or [this link](https://www.glfw.org/)
- [GLAD](https://github.com/Dav1dde/glad) or [this link](https://glad.dav1d.de/)
- [ImGui](https://github.com/ocornut/imgui)

You can find the licenses to the code inside their specific folders.
