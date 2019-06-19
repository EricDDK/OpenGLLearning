cmake_minimum_required (VERSION 3.4)
list(APPEND CMAKE_CXX_FLAGS "-std=c++11")
project (OpenGLLearning)
find_package(OpenGL REQUIRED)

include_directories("./build")
include_directories("./include")
LINK_DIRECTORIES("./libs")

if(WIN32)
  set(LIBS glfw3 opengl32)
elseif(UNIX AND NOT APPLE)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
  find_package(OpenGL REQUIRED)
  add_definitions(${OPENGL_DEFINITIONS})
  find_package(X11 REQUIRED)
  set(LIBS ${GLFW3_LIBRARY} X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread ${ASSIMP_LIBRARY})
  set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
elseif(APPLE)
  INCLUDE_DIRECTORIES(/System/Library/Frameworks)
  FIND_LIBRARY(COCOA_LIBRARY Cocoa)
  FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
  FIND_LIBRARY(IOKit_LIBRARY IOKit)
  FIND_LIBRARY(CoreVideo_LIBRARY CoreVideo)
  MARK_AS_ADVANCED(COCOA_LIBRARY OpenGL_LIBRARY)
  SET(APPLE_LIBS ${COCOA_LIBRARY} ${IOKit_LIBRARY} ${OpenGL_LIBRARY} ${CoreVideo_LIBRARY})
  SET(APPLE_LIBS ${APPLE_LIBS} ${GLFW3_LIBRARY} ${ASSIMP_LIBRARY})
  set(LIBS glfw3 ${LIBS} ${APPLE_LIBS})
else()
  set(LIBS )
endif(WIN32)

add_executable(
    main_1_1
    project/1.1_hello_windows/main.cpp
    project/glad.c
)
target_link_libraries(main_1_1 ${LIBS})

add_executable(
    main_1_2_1
    project/1.2_hello_triangle/main.cpp
    project/glad.c
)
target_link_libraries(main_1_2_1 ${LIBS})
add_executable(
    main_1_2_2
    project/1.2_hello_triangle/main_2.cpp
    project/glad.c
)
target_link_libraries(main_1_2_2 ${LIBS})

add_executable(
    main_1_3
    project/1.3_shader/main.cpp
    project/glad.c
)
target_link_libraries(main_1_3 ${LIBS})
add_executable(
    main_1_3_2
    project/1.3_shader/main_2.cpp
    project/glad.c
)
target_link_libraries(main_1_3_2 ${LIBS})
add_executable(
    main_1_3_3
    project/1.3_shader/main_3.cpp
    project/glad.c
)
target_link_libraries(main_1_3_3 ${LIBS})

add_executable(
    main_1_4
    project/1.4_texture/main.cpp
    project/glad.c
)
target_link_libraries(main_1_4 ${LIBS})
add_executable(
    main_1_4_2
    project/1.4_texture/main_2.cpp
    project/glad.c
)
target_link_libraries(main_1_4_2 ${LIBS})

add_executable(
    main_1_5
    project/1.5_transformations/main.cpp
    project/glad.c
)
target_link_libraries(main_1_5 ${LIBS})

add_executable(
    main_1_6
    project/1.6_coordinate_system/main.cpp
    project/glad.c
)
target_link_libraries(main_1_6 ${LIBS})
add_executable(
    main_1_6_2
    project/1.6_coordinate_system/main_2.cpp
    project/glad.c
)
target_link_libraries(main_1_6_2 ${LIBS})
add_executable(
    main_1_6_3
    project/1.6_coordinate_system/main_3.cpp
    project/glad.c
)
target_link_libraries(main_1_6_3 ${LIBS})

add_executable(
    main_1_7
    project/1.7_camera/main.cpp
    project/glad.c
)
target_link_libraries(main_1_7 ${LIBS})
add_executable(
    main_1_7_2
    project/1.7_camera/main_2.cpp
    project/glad.c
)
target_link_libraries(main_1_7_2 ${LIBS})
add_executable(
    main_1_7_3
    project/1.7_camera/main_3.cpp
    project/glad.c
)
target_link_libraries(main_1_7_3 ${LIBS})
