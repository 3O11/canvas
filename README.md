# canvas

This is a small library that I'm cobbling together to simplify the process of
making verious Computer Graphics showcases and examples. So far, I've only made
a lot more work for myself, but hopefully, sometime in the future, I'm not
going to regret the time spent on this.

The project is currently undergoing a fairly large rewrite - which might be
surprising, given there is not that much code yet. It is a painful lesson in
why a lone programmer with little experience probably shouldn't be designing a
whole library.

## Documentation

There is no documentation yet. I'm planning on adding documentation comments
in the process of cleaning up in various places. I also have plans to add
tests, but I'm not sure that there is that much to actually test yet (tests
will become very relevant once there are some actual algorithms).

Some proper documentation is also in the works, but it's not decided in what
format the documentation will be presented.

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
