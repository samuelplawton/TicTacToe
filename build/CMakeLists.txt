cmake_minimum_required(VERSION 3.16)
project(TicTacToe CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Grab all .cpp files in src/
file(GLOB SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")

# If you don't have a main yet, create src/main.cpp (see next step)
add_executable(TicTacToe ${SOURCES})
target_include_directories(TicTacToe PRIVATE "${CMAKE_SOURCE_DIR}/include")
