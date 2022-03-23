#pragma once

#include "camera.h"

namespace engine
{
	class ENGINE_API thirdPersonCamera : public camera
	{
	public:
		thirdPersonCamera(renderer* currentRenderer, float fieldOfView, float nearClip, float farClip);
		void updateCamera(glm::vec3 targetPosition, glm::vec2 deltaMouse, float distanceToTarget, float targetRotY);
	protected:
		void updateCameraTransform() override;
	private:
		float angleAroundPlayer;
		glm::vec3 targetPosition;
	};
}