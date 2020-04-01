cmake_minimum_required (VERSION 3.8)


add_subdirectory(logging)

add_executable (Blast2D "main.cpp" project.rc)

target_link_libraries(Blast2D logging-lib)