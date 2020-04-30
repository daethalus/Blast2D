cmake_minimum_required (VERSION 3.8)

project(game-lib)

file(GLOB_RECURSE game-src
        "*.hpp"
        "*.h"
        "*.cpp"
)

add_library (game-lib ${game-src})

target_compile_features(game-lib PRIVATE cxx_std_17)