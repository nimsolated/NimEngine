# src/CMakeLists.txt

# Find OpenGL
find_package(OpenGL REQUIRED)

# Engine executable
add_executable(NimEngine
    main.cpp
    Input.cpp
    Camera.cpp
    Shader.cpp
    Texture.cpp
)

# Include our public headers
target_include_directories(NimEngine PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/external/stb
)

# Link in GLFW, GLAD, and OpenGL
target_link_libraries(NimEngine PRIVATE
    glfw
    glad
    ${OPENGL_gl_LIBRARY}
    glm
)

# Copy entire assets/ into output directory
add_custom_command(TARGET NimEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:NimEngine>/assets
)