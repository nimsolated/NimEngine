#include "../include/Input.h"

void Input::init(GLFWwindow* window) {
	s_Window = window;
	// Set GLFW to call mouseCallback whenever mouse moves
	glfwSetCursorPosCallback(window, mouseCallback);
}

bool Input::isKeyPressed(int key) {
	return glfwGetKey(s_Window, key) == GLFW_PRESS;
}

void Input::mouseCallback(GLFWwindow* /*window*/, double xpos, double ypos) {
	s_MouseX = xpos;
	s_MouseY = ypos;
}

float Input::getMouseX() {
	return static_cast<float>(s_MouseX);
}

float Input::getMouseY() {
	return static_cast<float>(s_MouseY);
}