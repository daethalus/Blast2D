cmake_minimum_required (VERSION 3.8)


add_subdirectory(core/logging)
add_subdirectory(core/system)
add_subdirectory(modules/graphics)

add_executable (Blast2D "main.cpp" project.rc)

target_link_libraries(Blast2D core-logging-lib)
target_link_libraries(Blast2D core-system-lib)
target_link_libraries(Blast2D module-graphics-lib)

target_compile_features("Blast2D" PRIVATE cxx_std_17)