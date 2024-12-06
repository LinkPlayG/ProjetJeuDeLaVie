# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(ProjetJeuDeLaVie VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the compile options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Werror")
set(SFML_LIBS "-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system")

# Locate source and header files
file(GLOB_RECURSE SOURCES "../src/*.cpp")
file(GLOB_RECURSE HEADERS "../hea/*.h")

# Exclude .ccls-cache directories
list(FILTER SOURCES EXCLUDE REGEX ".*\\.ccls-cache.*")
list(FILTER HEADERS EXCLUDE REGEX ".*\\.ccls-cache.*")

# Main executable target
add_executable(GOL ${SOURCES} ${HEADERS} ../main.cpp)
target_link_libraries(GOL PRIVATE ${SFML_LIBS})