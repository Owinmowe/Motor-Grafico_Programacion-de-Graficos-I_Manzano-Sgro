#pragma once
#include "exports.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace engine
{
	class renderer;

	class ENGINE_API camera
	{
	public:
		camera(renderer* currentRenderer, float fieldOfView, float nearClip, float farClip);
		void moveCameraByGlobalVector(glm::vec3 movePosition);
		void moveCameraByLocalVector(glm::vec3 movePosition);
	protected:
		virtual void updateCameraTransform();
		void updateCameraVectors();
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		glm::vec3 positionVector;
		glm::vec3 rightVector;
		glm::vec3 frontVector;
		glm::vec3 upVector;
		float yaw;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
		float pitch;
		renderer* currentRenderer;
	};
}