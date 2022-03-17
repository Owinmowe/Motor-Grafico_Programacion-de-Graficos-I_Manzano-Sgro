#include "camera.h"
#include "renderer.h"

namespace engine
{
	camera::camera(renderer* currentRenderer, glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upVector, float fieldOfView, float nearClip, float farClip)
	{
		this->currentRenderer = currentRenderer;

		//TODO agregar propiedades/posibilidad de camara ortogonal
		projectionMatrix = glm::perspective(fieldOfView, (float)currentRenderer->getCurrentWindow()->getWidth() / (float)currentRenderer->getCurrentWindow()->getHeight(), nearClip, farClip);
		this->currentRenderer->setProjectionMatrix(projectionMatrix);
		setCameraTransform(position, lookPosition, upVector);
	}
	void camera::setCameraTransform(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector)
	{
		pos = startingPosition;
		look = lookPosition;
		up = upVector;
		viewMatrix = glm::lookAt(startingPosition, lookPosition, upVector);
		currentRenderer->setViewMatrix(viewMatrix);
	}
	void camera::moveCamera(glm::vec3 movePosition)
	{
		pos += movePosition;
		look += movePosition;
		setCameraTransform(pos, look, up);
	}
	void camera::changeCameraAim(float xoffset, float yoffset, bool constrainPitch)
	{

	}
	camera::~camera()
	{

	}
}