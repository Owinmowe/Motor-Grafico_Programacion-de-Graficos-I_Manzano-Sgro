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

		angleAroundPlayer += deltaMouse.x;
		this->yaw = 180 - targetRotY + angleAroundPlayer;

		this->targetPosition = targetPosition;
		float horizontalDistance = distanceToTarget * glm::cos(glm::radians(pitch));
		float verticalDistance = distanceToTarget * glm::sin(glm::radians(pitch));

		float theta = targetRotY + angleAroundPlayer;
		float offsetX = horizontalDistance * glm::sin(glm::radians(theta));
		float offsetZ = horizontalDistance * glm::cos(glm::radians(theta));

		v3pos.x = this->targetPosition.x - offsetX;
		v3pos.y = this->targetPosition.y + verticalDistance;
		v3pos.z = this->targetPosition.z - offsetZ;
		updateCameraTransform();
		updateCameraVectors();
	}
	void thirdPersonCamera::updateCameraTransform()
	{
		glm::vec3 cameraLookAt = glm::normalize(targetPosition - v3pos);
		viewMatrix = glm::lookAt(v3pos, v3pos + cameraLookAt, upVector);
		currentRenderer->setViewMatrix(viewMatrix);
	}
}