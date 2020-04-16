cmake_minimum_required (VERSION 3.8)

project(core-logging-lib)

file(GLOB core-logging-src
    "*.h"	
    "*.cc"
)
add_library (core-logging-lib ${core-logging-src})
target_compile_features(core-logging-lib PRIVATE cxx_std_17)