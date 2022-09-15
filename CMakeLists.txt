cmake_minimum_required(VERSION 3.14)
project(bombaklad)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(SOURCE_FILES main.cpp src/WaveFunctions.h src/Utils.h src/shapes/Wave.cpp src/shapes/Wave.h)
add_executable(bombaklad ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(bombaklad sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

# Setting ASSETS_PATH
target_compile_definitions(bombaklad PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets") # Set the asset path macro in release mode to a relative path that assumes the assets folder is in the same directory as the game executable

target_compile_definitions(bombaklad PUBLIC SHADERS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/") # Set the asset path macro to the absolute path on the dev machine
#target_compile_definitions(${PROJECT_NAME} PUBLIC SHADERS_PATH="./src/shaders") # Set the asset path macro in release mode to a relative path that assumes the assets folder is in the same directory as the game executable