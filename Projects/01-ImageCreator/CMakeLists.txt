add_executable (01-ImageCreator
	"main.cpp"
	"cgg_logo.h"
)

target_link_libraries (01-ImageCreator
	canvas
)

set_property(TARGET 01-ImageCreator PROPERTY CXX_STANDARD 20)
