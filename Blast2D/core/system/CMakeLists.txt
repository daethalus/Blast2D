cmake_minimum_required (VERSION 3.8)


project(core-system-lib)

file(GLOB core-system-src
    "*.hpp"
    "*.cpp"
)

add_library (core-system-lib ${core-system-src})

target_compile_features(core-system-lib PRIVATE cxx_std_17)


