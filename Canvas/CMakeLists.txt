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
	"Realtime/Window/Window.h"
	"Realtime/Window/Window.cpp"
	"Realtime/Window/ImguiWindow.h"
	"Realtime/OpenGL/Shader.h"
	"Realtime/OpenGL/Shader.cpp"
	"Realtime/OpenGL/Texture.h"
	"Realtime/OpenGL/Texture.cpp"
	"Realtime/OpenGL/Buffers.h"
	"Realtime/OpenGL/Buffers.cpp"
	"Debug/PrintFunctions.h"
	"Debug/PrintFunctions.cpp"
)

target_include_directories (canvas PUBLIC
	"Base"
	"Base/Math"
	"Base/Colour"
	"Base/Image"
	"Realtime"
	"Realtime/Window"
	"Realtime/OpenGL"
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
