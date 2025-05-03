#include "../include/Camera.h"

Camera::Camera(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch)
	: m_Position(position), m_WorldUp(up), m_Yaw(yaw), m_Pitch(pitch)
{
	updateCameraVectors();
	// Default projection
	m_ProjectionMatrix = glm::mat4(1.0f);
}

void Camera::setPerspective(float fovDeg, float aspect, float nearPlane, float farPlane) {
	m_ProjectionMatrix = glm::perspective(glm::radians(fovDeg), aspect, nearPlane, farPlane);
}

void Camera::processKeyboard(const glm::vec3& dir, float dt) {
	float velocity = m_MovementSpeed * dt;
	m_Position += dir * velocity;
	updateCameraVectors();
}

void Camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
	xOffset *= m_MouseSensitivity;
	yOffset *= m_MouseSensitivity;
	m_Yaw += xOffset;
	m_Pitch += yOffset;
	if (constrainPitch) {
		if (m_Pitch > 89.0f) {
			m_Pitch = 89.0f;
		}
		else if (m_Pitch < -89.0f) {
			m_Pitch = -89.0f;
		}
	}
	updateCameraVectors();
}

void Camera::updateCameraVectors() {
	glm::vec3 front;
	front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = sin(glm::radians(m_Pitch));
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(front);
	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));

	// Re-compute view matrix
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}