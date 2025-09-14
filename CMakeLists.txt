cmake_minimum_required(VERSION 3.20)
project(buildtemplate LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Put binaries under build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Library (rename/remove later if you want)
add_library(buildtemplate
    src/Example.cpp
)
target_include_directories(buildtemplate PUBLIC include)

# App / CLI
add_executable(buildtemplate_app
    src/main.cpp
)
target_link_libraries(buildtemplate_app PRIVATE buildtemplate)

# Platform flags (optional)
if (WIN32)
  target_compile_definitions(buildtemplate_app PRIVATE BT_WINDOWS)
elseif(APPLE)
  target_compile_definitions(buildtemplate_app PRIVATE BT_MACOS)
else()
  target_compile_definitions(buildtemplate_app PRIVATE BT_LINUX)
endif()
