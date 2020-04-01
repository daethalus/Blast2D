cmake_minimum_required (VERSION 3.8)

project(logging-lib)

file(GLOB logging-src
    "*.h"	
    "*.cc"
)
add_library (logging-lib ${logging-src})
target_compile_features(logging-lib PRIVATE cxx_std_17)