cmake_minimum_required(VERSION 3.16)
project(ProjetJeuDeLaVie)

set(CMAKE_CXX_STANDARD 20)

file(GLOB HEADERS_FILES hea/*.h)

file(GLOB SOURCE_FILES src/*.cpp)

add_executable(ProjetJeuDeLaVie ${SOURCE_FILES} ${HEADERS_FILES} main.cpp)