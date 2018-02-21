cmake_minimum_required(VERSION 3.9)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(BitQuest)

#### SETUP DIRECTORIES ####

# MAIN OUTPUT DIRECTORY
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")

# OUTPUT ALL DLLS FROM ALL LIBS INTO MAIN BUILD FOLDER
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")
add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/res" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res)

#### BitQuest ####
file (GLOB_RECURSE SOURCES Code/*.cpp Code/*.h)
add_executable(Bitquest ${SOURCES})
target_include_directories(Bitquest SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(Bitquest sfml-graphics)
add_dependencies(Bitquest copy_resources)
set_target_properties(Bitquest PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration))