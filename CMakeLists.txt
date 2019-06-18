cmake_minimum_required (VERSION 3.4)
add_compile_options(-std=c++11)
project (OpenGLLearning)
find_package(OpenGL REQUIRED)

include_directories("./include")
LINK_DIRECTORIES("./libs")

add_executable(
    main_1_1
    project/1.1_hello_windows/main.cpp
    project/glad.c
)
target_link_libraries(main_1_1 glfw3 ${OPENGL_gl_LIBRARY})

add_executable(
    main_1_2_1
    project/1.2_hello_triangle/main.cpp
    project/glad.c
)
target_link_libraries(main_1_2_1 glfw3 ${OPENGL_gl_LIBRARY})

add_executable(
    main_1_2_2
    project/1.2_hello_triangle/main_2.cpp
    project/glad.c
)
target_link_libraries(main_1_2_2 glfw3 ${OPENGL_gl_LIBRARY})

add_executable(
    main_1_3
    project/1.3_shader/main.cpp
    project/glad.c
)
target_link_libraries(main_1_3 glfw3 ${OPENGL_gl_LIBRARY})

add_executable(
    main_1_3_2
    project/1.3_shader/main_2.cpp
    project/glad.c
)
target_link_libraries(main_1_3_2 glfw3 ${OPENGL_gl_LIBRARY})

add_executable(
    main_1_3_3
    project/1.3_shader/main_3.cpp
    project/glad.c
)
target_link_libraries(main_1_3_3 glfw3 ${OPENGL_gl_LIBRARY})

add_executable(
    main_1_4
    project/1.4_texture/main.cpp
    project/glad.c
)
target_link_libraries(main_1_4 glfw3 ${OPENGL_gl_LIBRARY})