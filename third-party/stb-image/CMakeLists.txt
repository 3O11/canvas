add_library (stb-image STATIC
	"stb_image.h"
	"stb_image.c"
	"stb_image_write.h"
	"stb_image_write.c"
)

target_include_directories (stb-image INTERFACE
	"."
)

set_property(TARGET stb-image PROPERTY CXX_STANDARD 20)
