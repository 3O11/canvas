add_library (canvas-common STATIC
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
	"Animation/BasicAnimator.h"
	"Animation/BasicAnimator.cpp"
)

target_include_directories (canvas-common PUBLIC
	"Base"
	"Colour"
	"Image"
	"Math"
)

target_link_libraries (canvas-common PRIVATE
	stb-image	
)

set_property(TARGET canvas-common PROPERTY CXX_STANDARD 20)

if(MSVC)
  target_compile_options(canvas-common PRIVATE /W4 /WX)
else()
  target_compile_options(canvas-common PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()