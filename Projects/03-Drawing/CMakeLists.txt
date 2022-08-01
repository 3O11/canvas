add_executable(03-Drawing
    "main.cpp"
    "canvas.cpp"
)

set_property(TARGET 03-Drawing PROPERTY CXX_STANDARD 20)

target_link_libraries (03-Drawing
	canvas
)
