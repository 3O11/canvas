add_library (canvas STATIC
	"Base/Math/Types.h"
	"Base/Math/Vector.h"
	"Base/Math/Matrix.h"
	"Base/Math/Quaternion.h"
	"Base/Math/Transforms.h"
	"Base/Math/Transforms.cpp"
	"Base/Math/Utils.h"
	"Base/Math/Utils.cpp"
	"Base/CanvasMath.h"
	"Base/Colour/RGB.h"
	"Base/Colour/RGB.cpp"
	"Base/Colour/ColourAtlas.h"
	"Base/Colour/ColourUtils.h"
	"Base/Colour/ColourUtils.cpp"
	"Base/Image/Image.h"
	"Base/Image/Image.cpp"
	"Base/Image/ImageUtils.h"
	"Base/Image/ImageUtils.cpp"
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
	"Base/Math"
	"Base/Colour"
	"Base/Image"
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
