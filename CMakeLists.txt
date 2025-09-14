cmake_minimum_required(VERSION 3.20)
project(tictactoe LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
  main.cpp
  src/Logic.cpp
  # src/Interface.cpp   # leave out if it has its own main()
)

target_include_directories(${PROJECT_NAME} PRIVATE
  "${CMAKE_SOURCE_DIR}/src"
  "${CMAKE_SOURCE_DIR}/include"
)

# Embed icon from app.ico
if(WIN32 AND EXISTS "${CMAKE_SOURCE_DIR}/app.ico")
  file(WRITE "${CMAKE_BINARY_DIR}/appicon.rc"
    "IDI_APP_ICON ICON \"${CMAKE_SOURCE_DIR}/app.ico\"\n")
  target_sources(${PROJECT_NAME} PRIVATE "${CMAKE_BINARY_DIR}/appicon.rc")
endif()

# Static runtime for a more standalone feel
if(MSVC)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

