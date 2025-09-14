cmake_minimum_required(VERSION 3.16)

project(tictactoe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find all .cpp in src/
file(GLOB SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
message(STATUS "Sources: ${SOURCES}")

add_executable(tictactoe ${SOURCES})
target_include_directories(tictactoe PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")