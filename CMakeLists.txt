cmake_minimum_required (VERSION 3.8)

project ("Blast2D")

include_directories("Blast2D")

add_subdirectory ("Blast2D")

target_compile_features("Blast2D" PRIVATE cxx_std_17)
