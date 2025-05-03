cmake_minimum_required(VERSION 3.10)
project(MyEngine
    VERSION 0.1
    DESCRIPTION "Hybrid 2D/3D Game Engine (OpenGL, cross-platform)"
    LANGUAGES CXX
)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable out-of-source builds
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "In-source builds are not allowed. Please make a build directory.")
endif()

# Make our include/ directory visible
include_directories(${PROJECT_SOURCE_DIR}/include)

# Subdirectories
add_subdirectory(external)   # for GLFW, GLAD-fetch, etc. (we'll set this up next)
add_subdirectory(src)        # your engine code

# Installation rules (optional later)
# install(TARGETS NimEngine DESTINATION bin)
