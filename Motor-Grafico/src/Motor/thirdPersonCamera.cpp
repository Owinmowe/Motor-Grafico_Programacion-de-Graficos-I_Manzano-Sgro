#include "thirdPersonCamera.h"
#include "renderer.h"

namespace engine
{
	thirdPersonCamera::thirdPersonCamera(renderer* currentRenderer, float fieldOfView, float nearClip, float farClip) :
		camera(currentRenderer, fieldOfView, nearClip, farClip)
	{
		angleAroundPlayer = 0;
		targetPosition = glm::vec3(0, 0, 0);
	}
	void thirdPersonCamera::updateCamera(glm::vec3 targetPosition, glm::vec2 deltaMouse, float distanceToTarget, float targetRotY)
	{
		this->targetPosition = targetPosition;
		float horizontalDistance = distanceToTarget * glm::cos(glm::radians(pitch));
		float verticalDistance = distanceToTarget * glm::sin(glm::radians(pitch));

		angleAroundPlayer += deltaMouse.x;

		float theta = targetRotY + angleAroundPlayer;
		float offsetX = horizontalDistance * glm::sin(glm::radians(theta));
		float offsetZ = horizontalDistance * glm::cos(glm::radians(theta));

		positionVector.x = this->targetPosition.x - offsetX;
		positionVector.y = this->targetPosition.y + verticalDistance;
		positionVector.z = this->targetPosition.z - offsetZ;
		updateCameraTransform();
		updateCameraVectors();
	}
	void thirdPersonCamera::updateCameraTransform()
	{
		glm::vec3 cameraLookAt = targetPosition - positionVector;
		viewMatrix = glm::lookAt(positionVector, cameraLookAt, upVector);
		currentRenderer->setViewMatrix(viewMatrix);
	}
}