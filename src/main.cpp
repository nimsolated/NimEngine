#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../include/Input.h"
#include "../include/Camera.h"
#include <glm/glm.hpp>

class Scene {
public:
    virtual void update(float dt) = 0;
    virtual void render() = 0;
    virtual ~Scene() = default;
};

class BasicScene : public Scene {
public:
    BasicScene() : camera({ 0,0,3 }, { 0,1,0 }, -90.0f, 0.0f) {
        // Create camera at (0, 0, 3), looking towards -Z
        // initialize mouse-pos so the first delta is zero
        lastX = Input::getMouseX();
        lastY = Input::getMouseY();
        camera.setPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    }
    
    void update(float dt) override {
        // close on ESC
        if (Input::isKeyPressed(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
        }

        // move forward/back/strafe
        if (Input::isKeyPressed(GLFW_KEY_W)) {
            camera.processKeyboard(camera.getFront(), dt);
        }
        if (Input::isKeyPressed(GLFW_KEY_S)) {
            camera.processKeyboard(-camera.getFront(), dt);
        }
        if (Input::isKeyPressed(GLFW_KEY_A)) {
            camera.processKeyboard(-camera.getRight(), dt);
        }
        if (Input::isKeyPressed(GLFW_KEY_D)) {
            camera.processKeyboard(camera.getRight(), dt);
        }

        // mouse look
        float x = Input::getMouseX();
        float y = Input::getMouseY();
        camera.processMouseMovement(x - lastX, lastY - y);
        lastX = x;
        lastY = y;
    }

    void render() override {
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = camera.getProjectionMatrix();

        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
private:
    Camera camera;
    float lastX;
    float lastY;
};

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Request OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "NimEngine", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window.\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // Initialize the input system
    Input::init(window);

    // Timing
    float lastFrameTime = static_cast<float>(glfwGetTime());

    // Create and use a scene
    BasicScene scene;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        float now = static_cast<float>(glfwGetTime());
        float deltaTime = now - lastFrameTime;
        lastFrameTime = now;

        /*
        ****** UPDATE INPUT AND GAME LOGIC
        */
        scene.update(deltaTime);

        /*
        ****** RENDER
        */
        scene.render();

        /*
        ****** SWAP AND POLL EVENTS
        */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
