# external/CMakeLists.txt

# 1) GLFW
add_subdirectory(glfw)

# 2) GLAD
add_library(glad STATIC
    glad/src/glad.c
)
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
)
