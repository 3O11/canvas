add_library (canvas STATIC
	"Base/Types.h"
	"Colour/RGB.h"
	"Colour/RGB.cpp"
	"Colour/ColourAtlas.h"
	"Colour/ColourUtils.h"
	"Colour/ColourUtils.cpp"
	"Image/Image.h"
	"Image/Image.cpp"
	"Image/ImageUtils.h"
	"Image/ImageUtils.cpp"
	"Math/Vector.h"
	"Math/Vector.cpp"
	"Math/Matrix.h"
	"Math/Matrix.cpp"
	"Math/Point.h"
	"Math/Point.cpp"
	"Math/Transforms.h"
	"Math/Transforms.cpp"
	"Math/Quaternion.h"
	"Math/Quaternion.cpp"
	"Math/Utils.h"
	"Math/Utils.cpp"
	"Drawing/Shape.h"
	"Drawing/Canvas.h"
	"Drawing/Canvas.cpp"
	"Window/Window.h"
	"Window/Window.cpp"
	"Window/ImguiWindow.h"
	"OpenGL/Shader.h"
	"OpenGL/Shader.cpp"
	"OpenGL/Texture.h"
	"OpenGL/Texture.cpp"
	"OpenGL/Buffers.h"
	"OpenGL/Buffers.cpp"
	"Debug/PrintFunctions.h"
	"Debug/PrintFunctions.cpp"
)

target_include_directories (canvas PUBLIC
	"Base"
	"Colour"
	"Image"
	"Math"
	"Drawing"
	"Window"
	"OpenGL"
	"Debug"
)

add_subdirectory(".third-party")
target_link_libraries (canvas PRIVATE
	stb-image
	glfw
)

target_link_libraries(canvas PUBLIC
	glad
	glfw
	imgui
)

set_property(TARGET canvas PROPERTY CXX_STANDARD 20)

if(MSVC)
	target_compile_options(canvas PRIVATE /W4 /WX)
else()
	target_compile_options(canvas PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
