add_executable (02-Window
	"main.cpp"
)

target_link_libraries (02-Window
	canvas
	glfw
)

set_property(TARGET 02-Window PROPERTY CXX_STANDARD 20)
