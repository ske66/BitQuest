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
#target_include_directories(Bitquest SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(Bitquest lib_tile_level_loader lib_ecm lib_maths sfml-graphics Box2D)
add_dependencies(Bitquest copy_resources)
set_target_properties(Bitquest PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration))

#### Tile loader lib ####
file(GLOB_RECURSE SOURCE_FILES lib_tile_level_loader/*.cpp lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES})
target_include_directories(lib_tile_level_loader INTERFACE "${CMAKE_SOURCE_DIR}/lib_tile_level_loader/" PRIVATE ${SFML_INCS})
target_link_libraries(lib_tile_level_loader lib_maths sfml-graphics)

#### Maths lib ####
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths" SYSTEM INTERFACE ${SFML_INCS})

#### ECM Library ####
file(GLOB_RECURSE SOURCE_FILES lib_ecm/*.cpp lib_ecm/*.h)
add_library(lib_ecm STATIC ${SOURCE_FILES})
target_include_directories(lib_ecm INTERFACE "${CMAKE_SOURCE_DIR}/lib_ecm")
target_link_libraries(lib_ecm PRIVATE lib_maths)

### Box 2d library ###
add_subdirectory(lib/b2d/Box2D)
include_directories("lib/b2d/Box2D")
set(B2D_INCS "lib/b2d/Box2D")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")