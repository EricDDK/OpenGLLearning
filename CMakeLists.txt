cmake_minimum_required (VERSION 3.4)
add_compile_options(-std=c++11)
project (OpenGLLearning)
find_package(OpenGL REQUIRED)

include_directories("./include")
LINK_DIRECTORIES("./libs")

add_executable(
    main_0
    main.cpp
    glad.c
)
target_link_libraries(main_0 glfw3 ${OPENGL_gl_LIBRARY})
