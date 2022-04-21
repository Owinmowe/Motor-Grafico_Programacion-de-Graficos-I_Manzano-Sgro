#include "camera.h"
#include "renderer.h"

namespace engine
{
	camera::camera(renderer* currentRenderer, float fieldOfView, float nearClip, float farClip)
	{
		this->currentRenderer = currentRenderer;
		//TODO agregar propiedades/posibilidad de camara ortogonal
		int currentWidth = currentRenderer->getCurrentWindow()->getWidth();
		int currentHeight = currentRenderer->getCurrentWindow()->getHeight();
		projectionMatrix = glm::perspective(fieldOfView, (float)currentWidth / (float)currentHeight, nearClip, farClip);

		updateCameraVectors();
		updateCameraTransform();
	}
	void camera::updateCameraTransform()
	{
		viewMatrix = glm::lookAt(v3pos, v3pos + frontVector, upVector);
		this->currentRenderer->setProjectionMatrix(projectionMatrix);
		currentRenderer->setViewMatrix(viewMatrix);
		currentRenderer->setCameraPosition(v3pos);
	}
	void camera::updateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		frontVector = glm::normalize(front);

		upVector = glm::vec3(0.0f, 1.0f, 0.0f);
		rightVector = glm::normalize(glm::cross(frontVector, upVector));
		upVector = glm::normalize(glm::cross(rightVector, frontVector));
	}
	void camera::moveCameraByGlobalVector(glm::vec3 movePosition)
	{
		v3pos += movePosition;
		updateCameraTransform();
	}
	void camera::moveCameraByLocalVector(glm::vec3 movePosition)
	{
		v3pos += rightVector * movePosition.x;
		v3pos += upVector * movePosition.y;
		v3pos -= frontVector * movePosition.z;
		updateCameraVectors();
		updateCameraTransform();
	}
	void camera::draw()
	{
		std::cout << "Draw function not implemented for the camera";
	}
}