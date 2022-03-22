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
		this->currentRenderer->setProjectionMatrix(projectionMatrix);

		glm::vec3 camStartingPos = { 0, 0, 250 };


		yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
		pitch = 0.0f;

		updateCameraVectors();

		setCameraTransform(camStartingPos, frontVector, rightVector, upVector);
	}
	void camera::setCameraTransform(glm::vec3 position, glm::vec3 front, glm::vec3 right, glm::vec3 up)
	{
		positionVector = position;
		frontVector = front;
		upVector = up;
		rightVector = right;
		viewMatrix = glm::lookAt(positionVector, positionVector + frontVector, upVector);
		currentRenderer->setViewMatrix(viewMatrix);
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
		positionVector += movePosition;
		updateCameraVectors();
		setCameraTransform(positionVector, frontVector, rightVector, upVector);
	}
	void camera::moveCameraByLocalVector(glm::vec3 movePosition)
	{
		positionVector += rightVector * movePosition.x;
		positionVector += upVector * movePosition.y;
		positionVector -= frontVector * movePosition.z;
		updateCameraVectors();
		setCameraTransform(positionVector, frontVector, rightVector, upVector);
	}
	void camera::changeCameraAim(float xoffset, float yoffset, bool constrainPitch)
	{
		//std::cout << "xoffset: " << xoffset << std::endl;
		//std::cout << "yoffset: " << yoffset << std::endl;
		yaw += xoffset;
		pitch += yoffset;

		if(constrainPitch)
		{
			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;
		}

		updateCameraVectors();
		setCameraTransform(positionVector, frontVector, rightVector, upVector);
	}
	camera::~camera()
	{

	}
}