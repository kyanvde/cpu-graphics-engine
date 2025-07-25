cmake_minimum_required(VERSION 3.28)

project(engine)

############################################################
# Set compiler flags
############################################################
set(OWN_GXX_FLAGS "-std=c++17 -Wall -Wextra -fstack-protector-all -g3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OWN_GXX_FLAGS}")

############################################################
# List all sources
############################################################
set(engine_sources
        src/engine.cpp
        src/model/Scene.cpp
        src/parser/JsonSceneParser.cpp
)

############################################################
# Create an executable
############################################################
add_executable( "engine" ${engine_sources} )