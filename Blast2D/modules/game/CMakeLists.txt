cmake_minimum_required (VERSION 3.8)

project(module-game-lib)

file(GLOB_RECURSE module-game-src
        "*.hpp"
        "*.h"
        "*.cpp"
)

add_library (module-game-lib ${module-game-src})

target_compile_features(module-graphics-lib PRIVATE cxx_std_17)