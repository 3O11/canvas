cmake_minimum_required (VERSION 3.20)

add_library(Common STATIC
	"Vector3.h"
	"Vector3.cpp"
)

target_include_directories(Common PUBLIC
	"."
)
