cmake_minimum_required (VERSION 3.8)

function(add_blast_module name)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_link_libraries(Blast2D ${name})
		message(Blast2D PROPERTIES LINK_FLAGS "/WHOLEARCHIVE:" ${name})
        set_target_properties(Blast2D PROPERTIES LINK_FLAGS "/WHOLEARCHIVE:${name}")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_libraries(Blast2D -Wl,--whole-archive ${name} -Wl,--no-whole-archive)
    endif()
endfunction()

add_subdirectory(core)
#add_subdirectory(game)
add_subdirectory(modules/graphics)

add_executable (Blast2D "main.cpp" "game.hpp" "game.cpp" project.rc)

add_blast_module(core-lib)
#add_blast_module(game-lib)
add_blast_module(module-graphics-lib)

target_compile_features("Blast2D" PRIVATE cxx_std_17)