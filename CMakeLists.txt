cmake_minimum_required(VERSION 3.0.0)

project(Fractal3k1)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

add_executable(frac3k1
	main.cpp
	app.cpp
	window.cpp
	main_window.cpp
	shader.cpp
	render_pass.cpp
	framebuffer.cpp
	framebuffer_pass.cpp
	fractal_pass.cpp)
target_link_libraries(frac3k1 ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} -lOpenGL -lpthread)
