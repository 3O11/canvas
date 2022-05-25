add_executable(04-Quaternions
    "main.cpp"
)

set_property(TARGET 04-Quaternions PROPERTY CXX_STANDARD 20)

target_link_libraries (04-Quaternions
	canvas
)
