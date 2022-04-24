#pragma once
#include "exports.h"
#include "entity.h"

namespace engine
{
	class renderer;

	class ENGINE_API camera : public entity
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
		renderer* currentRenderer;
	};
}