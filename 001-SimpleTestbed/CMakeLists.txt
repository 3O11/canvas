cmake_minimum_required (VERSION 3.20)

add_executable (SimpleTestbed
	"main.cpp"
)

set(BUILD_SHARED_LIBS OFF)
include(FetchContent)
FetchContent_Declare(
 SFML
 GIT_REPOSITORY https://github.com/SFML/SFML.git
 GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)

target_link_libraries (SimpleTestbed
	Common
	sfml-window
	sfml-graphics
)