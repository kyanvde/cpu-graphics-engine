cmake_minimum_required(VERSION 3.28)

project(engine)

############################################################
# Set compiler flags
############################################################
set(OWN_GXX_FLAGS "-std=c++17 -Wall -Wextra -fstack-protector-all -g3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OWN_GXX_FLAGS}")

############################################################
# List all sources
############################################################
set(engine_sources
        src/io/parsers/objects/LineDrawingParser.cpp
        src/io/parsers/objects/LSystem2DParser.cpp
        src/io/parsers/JsonSceneParser.cpp
        src/io/writers/BMPWriter.cpp
        src/math/Projector.cpp
        src/model/objects/LineDrawing.cpp
        src/model/objects/LSystem2D.cpp
        src/model/Image.cpp
        src/model/Scene.cpp
)

set(test_sources
        tests/MathUtilsTest.cpp
        tests/Vec3Test.cpp
        tests/ProjectorTest.cpp
        tests/MatrixTest.cpp
        tests/SceneObjectTest.cpp
        tests/SceneTest.cpp
)
############################################################
# Add dependencies
############################################################
include(FetchContent)

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)

############################################################
# Create executables
############################################################
add_executable(engine src/engine.cpp ${engine_sources})
target_include_directories(engine PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(engine PRIVATE nlohmann_json::nlohmann_json)

add_executable(engine_tests ${engine_sources} ${test_sources})
target_include_directories(engine_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(engine_tests PRIVATE nlohmann_json::nlohmann_json gtest_main)

enable_testing()
add_test(NAME EngineTests COMMAND engine_tests)