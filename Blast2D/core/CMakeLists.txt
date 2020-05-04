cmake_minimum_required (VERSION 3.8)

project(core-lib)

file(GLOB_RECURSE core-src
        "*.hpp"
        "*.h"
        "*.cpp"
        "*.cc"
        )

add_library (core-lib ${core-src})

target_compile_features(core-lib PRIVATE cxx_std_17)


