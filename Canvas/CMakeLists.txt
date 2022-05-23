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
	"Image/Drawing.h"
	"Image/Drawing.cpp"
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
	"Animation/BasicAnimator.h"
	"Animation/BasicAnimator.cpp"
	"Drawing/Shape.h"
	"Drawing/Canvas.h"
	"Drawing/Canvas.cpp"
	"Drawing/Shapes/Circle.h"
	"Drawing/Shapes/Circle.cpp"
	"Window/Window.h"
	"Window/Window.cpp"
	"Window/ImguiWindow.h"
)

target_include_directories (canvas PUBLIC
	"Base"
	"Colour"
	"Image"
	"Math"
	"Animation"
	"Drawing"
	"Window"
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
