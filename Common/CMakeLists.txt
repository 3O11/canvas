add_library (canvas-common STATIC
	"Colour/RGB.h"
	"Colour/RGB.cpp"
	"Image/Image.h"
	"Image/Image.cpp"
	"Image/Drawing.h"
	"Image/Drawing.cpp"
)

target_include_directories (canvas-common INTERFACE
	"Image"
	"Colour"
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