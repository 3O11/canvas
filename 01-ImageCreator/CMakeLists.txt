add_executable (ImageCreator
	"main.cpp"
	"cgg_logo.h"
)

target_link_libraries (ImageCreator
	canvas-common
)

set_property(TARGET ImageCreator PROPERTY CXX_STANDARD 20)
