#pragma once
#include <GLFW/glfw3.h>

class Input {
private:
	static inline GLFWwindow* s_Window = nullptr;
	static inline double s_MouseX = 0.0;
	static inline double s_MouseY = 0.0;
public:
	// Initialize with your GLFW window
	static void init(GLFWwindow* window);

	// Query keys
	static bool isKeyPressed(int key);

	// Mouse callbacks
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	static float getMouseX();
	static float getMouseY();
};