cmake_minimum_required (VERSION 3.8)

project ("Blast2D")

include_directories("Blast2D")

add_subdirectory ("Blast2D")

INSTALL (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Blast2D/
        DESTINATION ${CMAKE_BINARY_DIR}/includes/
        FILES_MATCHING PATTERN "*.h*")
