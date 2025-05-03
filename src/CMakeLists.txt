# src/CMakeLists.txt

# Find OpenGL
find_package(OpenGL REQUIRED)

# Engine executable
add_executable(NimEngine
    main.cpp
)

# Include our public headers
target_include_directories(NimEngine PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

# Link in GLFW, GLAD, and OpenGL
target_link_libraries(NimEngine PRIVATE
    glfw
    glad
    ${OPENGL_gl_LIBRARY}
)
