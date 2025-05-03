#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	// Constructor: position, world-up, yaw (deg), pitch (deg)
	Camera(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch);

	// Set perspective projection params
	void setPerspective(float fovDeg, float aspect, float nearPlane, float farPlane);

	// Call each frame if you want to move the camera
	void processKeyboard(const glm::vec3& direction, float deltaTime);
	void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

	// Fetch your matrices for passing to shaders
	const glm::mat4& getViewMatrix() const { return m_ViewMatrix; }
	const glm::mat4& getProjectionMatrix() const { return m_ProjectionMatrix; }

	// Front and right getters
	const glm::vec3& getFront() const { return m_Front; }
	const glm::vec3& getRight() const { return m_Right; }
private:
	// Re-calculates m_ViewMatrix and direction vectors
	void updateCameraVectors();

	// Camera attributes
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	glm::vec3 m_WorldUp;

	// Euler angles
	float m_Yaw;
	float m_Pitch;

	// Matrices
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;

	// Options
	float m_MovementSpeed = 2.5f;
	float m_MouseSensitivity = 0.1f;
};