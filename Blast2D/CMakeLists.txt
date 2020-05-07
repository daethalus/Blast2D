cmake_minimum_required (VERSION 3.8)

project(blast-lib)

function(add_blast_module name)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_link_libraries(Blast2D PUBLIC ${name})
		message(Blast2D PROPERTIES LINK_FLAGS "/WHOLEARCHIVE:" ${name})
        set_target_properties(Blast2D PROPERTIES LINK_FLAGS "/WHOLEARCHIVE:${name}")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_libraries(Blast2D PUBLIC -Wl,--whole-archive ${name} -Wl,--no-whole-archive)
    endif()
endfunction()


file(GLOB_RECURSE blast2d-src
        "*.cpp"
        "*.cc")

file(GLOB_RECURSE blast2d-inc
        "*.hpp"
        "*.h")

list(REMOVE_ITEM blast2d-src ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_library(blast-lib STATIC ${blast2d-src})
target_include_directories(blast-lib PUBLIC ${blast2d-inc})

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(blast-lib PUBLIC glfw)

set(OpenGL_GL_PREFERENCE "GLVND")

find_package(OpenGL REQUIRED)
target_include_directories(blast-lib PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(blast-lib PRIVATE ${OPENGL_gl_LIBRARY})

find_package(glad CONFIG REQUIRED)
target_link_libraries(blast-lib PUBLIC glad::glad)

target_compile_features(blast-lib PRIVATE cxx_std_17)

add_executable (Blast2D "main.cpp" project.rc)
target_compile_features(Blast2D PRIVATE cxx_std_17)
add_blast_module(blast-lib)