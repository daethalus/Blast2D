cmake_minimum_required (VERSION 3.8)


project(module-graphics-lib)

file(GLOB_RECURSE module-graphics-src
    "*.hpp"
    "*.cpp"
)

add_library (module-graphics-lib ${module-graphics-src})

target_compile_features(module-graphics-lib PRIVATE cxx_std_17)

#--libs

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(module-graphics-lib glfw)

set(OpenGL_GL_PREFERENCE "GLVND")

find_package(OpenGL REQUIRED)
target_include_directories(module-graphics-lib PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(module-graphics-lib ${OPENGL_gl_LIBRARY})

find_package(glad CONFIG REQUIRED)
target_link_libraries(module-graphics-lib glad::glad)


