cmake_minimum_required(VERSION 3.20)
project(tictactoe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Discover sources ----
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(SOURCES "")

# All sources under src/
if (EXISTS "${SRC_DIR}")
  file(GLOB_RECURSE SRC_SOURCES CONFIGURE_DEPENDS
       "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.cxx" "${SRC_DIR}/*.c")
  list(APPEND SOURCES ${SRC_SOURCES})
endif()

# Sources in repo root
file(GLOB ROOT_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_SOURCE_DIR}/*.cpp" "${CMAKE_SOURCE_DIR}/*.cxx" "${CMAKE_SOURCE_DIR}/*.c")

# Prefer src/main.cpp over root/main.cpp
set(ROOT_MAIN "${CMAKE_SOURCE_DIR}/main.cpp")
set(SRC_MAIN  "${SRC_DIR}/main.cpp")
if (EXISTS "${SRC_MAIN}" AND EXISTS "${ROOT_MAIN}")
  list(REMOVE_ITEM ROOT_SOURCES "${ROOT_MAIN}")
endif()

# Combine
list(APPEND SOURCES ${ROOT_SOURCES})

if (SOURCES STREQUAL "")
  message(FATAL_ERROR "No source files found. Put .cpp files in 'src/' or in the project root.")
endif()

# ---- Target ----
add_executable(tictactoe ${SOURCES})

# Include paths for headers
target_include_directories(tictactoe PRIVATE
  "${CMAKE_SOURCE_DIR}"
  "${CMAKE_SOURCE_DIR}/src"
  "${CMAKE_SOURCE_DIR}/include"
)

# Warnings
if (MSVC)
  target_compile_options(tictactoe PRIVATE /W4 /permissive-)
else()
  target_compile_options(tictactoe PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Optional: Windows icon (drop app.ico next to this file)
if (WIN32)
  set(APP_ICON "${CMAKE_SOURCE_DIR}/app.ico")
  if (EXISTS "${APP_ICON}")
    set(RC_PATH "${CMAKE_BINARY_DIR}/appicon.rc")
    file(WRITE "${RC_PATH}" "1 ICON \"${APP_ICON}\"\n")
    target_sources(tictactoe PRIVATE "${RC_PATH}")
  endif()
endif()
